#include "trajectory.h"

/* Public Functions */

Trajectory::Trajectory()
{
    this->numWaypoints = 0;
    this->currentWpt = 0;
}

Trajectory::Trajectory(const std::string& filename)
{
    this->numWaypoints = 0;
    this->currentWpt = 0;
    loadWaypoints(filename);
}

void Trajectory::appendWaypoints(const std::string& filename)
{
    loadWaypoints(filename);
}

void Trajectory::generateKMLOutput(const std::string& filename)
{
    std::string kml = "";
    kml += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    kml += "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n";
    kml += "\t<Document>\n";
    kml += "\t<Style id=\"SCR\">\n";
    kml += "\t\t<LineStyle>\n";
    kml += "\t\t\t<color>ff0000ff</color>\n";
    kml += "\t\t\t<width>1</width>\n";
    kml += "\t\t</LineStyle>\n";
    kml += "\t\t<PolyStyle>\n";
    kml += "\t\t\t<color>ffff0000</color>\n";
    kml += "\t\t</PolyStyle>\n";
    kml += "\t</Style>\n";
    kml += "\t\t<Placemark>\n";
    kml += "\t\t\t<name>Robot Path</name>\n";
    kml += "\t\t\t<visibility>1</visibility>\n";
    kml += "\t\t<LookAt>\n";
    kml += "\t\t\t<longitude>" + getWptKMLComponent(0, false) + "</longitude>\n";
    kml += "\t\t\t<latitude>" + getWptKMLComponent(0,true) + "</latitude>\n";
    kml += "\t\t\t<altitude>0</altitude>\n";
    kml += "\t\t\t<heading>0</heading>\n";
    kml += "\t\t\t<tilt>0</tilt>\n";
    kml += "\t\t\t<range>2000</range>\n";
    kml += "\t\t</LookAt>\n";
    kml += "\t\t<styleUrl>#SCR</styleUrl>\n";
    kml += "\t\t\t<LineString>\n";
    kml += "\t\t\t\t<extrude>1</extrude>\n";
    kml += "\t\t\t\t<tessellate>1</tessellate>\n";
    kml += "\t\t\t\t<altitudeMode>relativeToGround</altitudeMode>\n";
    kml += "\t\t\t\t<coordinates>\n";

    std::string coords = "", str = "";
    std::stringstream ss;

    for(int i = 0; i < this->numWaypoints; ++i)
    {
        coords += "\t\t\t\t" + getWptKMLCoords(i) + ",2000\n";
    }

    kml += coords;
    kml += "\t\t\t\t</coordinates>\n";
    kml += "\t\t\t</LineString>\n";
    kml += "\t\t</Placemark>\n";
    kml += "\t</Document>\n";
    kml += "</kml>\n";

    std::ofstream outputFile;
    outputFile.open(filename);
    outputFile << kml;
    outputFile.close();
}

void Trajectory::advanceToNextPoint()
{
    //The current waypoint is no longer on the active route
    this->waypoints[currentWpt].setEnrouteStatus(false);
    currentWpt++;
}

Waypoint* Trajectory::getActivePoint()
{
    return &this->waypoints[currentWpt];
}

Waypoint* Trajectory::getNextPoint()
{
    if((currentWpt + 1) < numWaypoints)
    {
        return &this->waypoints[currentWpt + 1];
    }
    return nullptr;
}


/* End Public Functions */
/* Private Functions    */

void Trajectory::loadWaypoints(const std::string& filename)
{
    std::stringstream decoder;
    std::ifstream file(filename);
    std::string line;

    Waypoint wpt;
    WaypointType wpt_type;
    float latitude, longitude;
    float degree, minute;
    char c;

    if(file.good())
    {
        while(std::getline(file, line))
        {
            decoder.str(line);

            /* Longitude Coordinate */
            decoder >> c;
            decoder >> degree;
            decoder >> minute;
            latitude = convertCoordinate(c, degree, minute);

            /* Latitude Coordinate  */
            decoder >> c;
            decoder >> degree;
            decoder >> minute;
            longitude = convertCoordinate(c, degree, minute);

            /* Waypoint Type        */
            decoder >> c;
            wpt_type = decodeWaypointType(c);

            /* Clear the stringstream */
            decoder.clear();

            /* Build the waypoint information */
            wpt.setLatitude(latitude);
            wpt.setLongitude(longitude);
            wpt.setType(wpt_type);

            /* Add the waypoint to the trajectory */
            push(wpt);

            /* Clear the waypoint for the next loop */
            wpt.reset();
        }

        file.close();
    }
}

float Trajectory::convertCoordinate(char c, float degree, float minute)
{
    int sign;
    float decimal = 0;

    /* Based on the direction, determine the sign of the value */
    switch(c)
    {
        case 'N':
        case 'n':
        case 'E':
        case 'e':
            sign = 1;
            break;
        case 'S':
        case 's':
        case 'W':
        case 'w':
            sign = -1;
            break;
        default:
            sign = 1;
            break;
    }

    /* Convert the input to decimal format */
    decimal = degree;
    decimal += (minute / 60);
    decimal *= sign;

    return decimal;
}

WaypointType Trajectory::decodeWaypointType(char abbreviation)
{
    switch(abbreviation)
    {
        /* S/s = Start Waypoint */
        case 's':
        case 'S':
            return START;
        /* E/e or F/f = Finish Waypoint */
        case 'e':
        case 'E':
        case 'f':
        case 'F':
            return FINISH;
        /* B/b = Bonus Waypoint */
        case 'b':
        case 'B':
            return BONUS;
        /* A/a = Adjustment Waypoint */
        case 'a':
        case 'A':
            return ADJUSTMENT;
        /* O/o or C/c = On-Course Waypoint */
        case 'o':
        case 'O':
        case 'c':
        case 'C':
            return ON_COURSE;
        default:
            return DEFAULT_WAYPOINT;
    }
}

void Trajectory::push(Waypoint wpt)
{
    if(this->numWaypoints >= 0 && this->numWaypoints < 200)
    {
        this->waypoints[numWaypoints] = wpt;
        this->numWaypoints++;
    }
}

std::string Trajectory::getWptKMLCoords(int i)
{
    std::stringstream ss;
    std::string coords = "";
    coords += getWptKMLComponent(i, false) + ",";
    coords += getWptKMLComponent(i, true);
    ss.clear();

    return coords;
}

std::string Trajectory::getWptKMLComponent(int i, bool lat)
{
    std::string str;
    std::stringstream ss;

    if(lat)
    {
        ss << this->waypoints[i].getLatitude();
    }
    else
    {
        ss << this->waypoints[i].getLongitude();
    }

    ss >> str;
    ss.clear();

    return str;
}

/* End Private Functions */

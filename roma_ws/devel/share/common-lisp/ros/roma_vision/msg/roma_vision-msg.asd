
(cl:in-package :asdf)

(defsystem "roma_vision-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "obstacles" :depends-on ("_package_obstacles"))
    (:file "_package_obstacles" :depends-on ("_package"))
  ))
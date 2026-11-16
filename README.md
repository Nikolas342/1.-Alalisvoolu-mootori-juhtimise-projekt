# 1.-Alalisvoolu-mootori-juhtimise-projekt
Funktsionaalsus: start, stop, kiirendus, aeglustus, suunavahetus.
# Nikolas Javorski TN3

Selle projekti eesmärk on juhtida alalisvoolumootorit (DC motor) mikrokontrolleri (Arduino) ja L298N H-silla abil. Süsteem võimaldab mootorit käivitada (`start`), peatada (`stop`), reguleerida kiirust PWM abil (vahemikus `0–255`), muuta pöörlemissuundu (`dir`) ning tagab sujuva kiirenduse ja aeglustuse.

main.ino on peamine fail, kuhu saab defineerida, mis mootoreid juhtida ning kuidas luua kommunikatsioon nendega

motorDriver.h on header fail, mis defineerib ära kuidas mootoreid juhitakse.

userInterface.h on header fail, mis defineerib kuidas toimub kommunikatsioon üle seriali ja mida saab üldse mootoritega teha.

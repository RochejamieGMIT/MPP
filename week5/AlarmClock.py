from Clock import *

class AlarmClock(Clock):
    def __init__(self,hours,mins,secs,aHour,aMin,aSec):
        super().__init__(hours,mins,secs)
        self.aHour = aHour
        self.aMin = aMin
        self.aSec = aSec

    def tick(self):
        super().tick()
        if(self.hours == self.aHour and self.mins == self.aMin and self.secs ==self.aSec):
            print("ALAAAAAAAAAAAAAARM")

    def __repr__(self):
        return f"Alarm: {super().__repr__()}"

if __name__ =="__main__":
    c = AlarmClock(10,20,46,10,20,49)
    c2 = Clock(11,55,58)
    arr = [c,c2]
    while(True):
        for clock in arr:
            print(clock)
            clock.tick()
            time.sleep(1)
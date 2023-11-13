import time

class Clock:
    def __init__(self,hours,mins,secs):
        self.hours = hours
        self.mins = mins
        self.secs = secs
        self.validate()

    def validate(self):
        if (self.hours > 12 or self.mins > 60 or self.secs > 60):
            self.hours = 0
            self.mins = 0
            self.secs = 0
    def tick(self):
        self.secs += 1

        if (self.secs > 59):
            self.mins +=1
            self.secs = 0
        
        if (self.mins > 59):
            self.hours +=1
            self.mins = 0
        
        if (self.hours > 12):
            self.hours = 1
            self.mins = 0
            self.secs = 0

    def __repr__(self):
        #return (str(self.hours)+":"+str(self.mins)+":"+str(self.secs))
        return f"{self.hours}:{self.mins}:{self.secs}"
if __name__ == "__main__":
    c = Clock(10,59,50)
    
    while(True):
        c.tick()
        print(c)
        time.sleep(1)
        
        
    
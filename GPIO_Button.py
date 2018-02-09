import RPi.GPIO as g
import time

class GPIO_Button():
    def __init__(self,pin,callback):
        g.setmode(g.BCM)
        g.setup(pin,g.IN)
        self.pin = pin
        self.unset=True
        self.callback = callback
        
    def check(self):
        if g.input(self.pin) and self.unset:
            self.unset=False
            self.callback()
            time.sleep(0.01)
        elif not g.input(self.pin) and not self.unset:
            self.unset = True


def debug_callback():
    print 'hi kevin!'
def debug2():
    print 'oh, its derek!'

    

if __name__ == "__main__":
    x = GPIO_Button(28,debug_callback)
    y = GPIO_Button(30,debug2)
    while True:
        x.check()
        y.check()

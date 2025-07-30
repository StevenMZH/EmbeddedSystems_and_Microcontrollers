import serial
import time

# Serial Transmition of the packages
def packagesTrasmition(data, port):
    # Configuration
    serialCom = serial.Serial(port, 9600)
    time.sleep(2)  # Wait to stablish conection
    
    serialCom.write(data.encode())
    time.sleep(0.1)  # tiny delay between communication

    # end conection
    print('Sucessfull Transmition\n')
    serialCom.close()


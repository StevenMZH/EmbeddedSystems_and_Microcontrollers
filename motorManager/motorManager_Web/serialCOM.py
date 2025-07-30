import serial
import time

# Serial Transmition of the packages
def packagesTrasmition(packages, port):

    # Configuration
    serialCom = serial.Serial(port, 9600)
    time.sleep(2)  # Wait to stablish conection

    for package in packages:
        serialCom.write(bytes([package]))
        time.sleep(0.1)  # tiny delay between communication

    # end conection
    print('Sucessfull Transmition\n')
    serialCom.close()


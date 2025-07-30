import json
from datetime import datetime

class processData:

    def __init__(self, requestNum, requestTime, speed, rotation, connection, timerType, time, timeMeasurement, conditionalType, condition):
        self.requestNum = requestNum
        self.requestTime = requestTime
        self.speed = speed
        self.rotation = rotation
        self.connection = connection
        self.timerType = timerType
        self.time = time
        self.timeMeasurement = timeMeasurement
        self.conditionalType = conditionalType
        self.condition = condition

    def printProcess(self):
        print(f"Request {self.requestNum}:")
        print(f"({self.requestTime})\n")
        print(f"  Speed: {self.speed}")
        print(f"  Rotation: {self.rotation}")
        print(f"  Connection: {self.connection}")
        print(f"  Timer Type: {self.timerType}")
        print(f"  Time: {self.time} {self.timeMeasurement}")
        print(f"  Conditional Type: {self.conditionalType}")
        print(f"  Condition: {self.condition}")
        print()

class Package:

    def __init__(self, requestNum, requestTime, data):
        self.requestNum = requestNum
        self.requestTime = requestTime
        self.data = data
    
    def printP(self):
        print(f"Request {self.requestNum}:")
        print(f"({self.requestTime})\n")
        print(f"  Package: {self.data}")


def readData(file):
    try:
        with open(file, 'r') as f:
            data = json.load(f)
            return [processData(**item) for item in reversed(data)]
    except FileNotFoundError:
        return []
    
def readPackage(file):
    try:
        with open(file, 'r') as f:
            data = json.load(f)
            return [Package(**item) for item in reversed(data)]
    except FileNotFoundError:
        return []
    
def printData(file):
    loadData = readData(file)
    print(f"\n# Request Record #\n")
    for data in loadData:
        data.printProcess()

def printPackage(file):
    loadData = readPackage(file)
    print(f"\n# Packages Record #\n")
    for packages in loadData:
        packages.printP()
        print("\n")

def writeData(file, data):
    try:
        with open(file, 'r') as f:
            existing_data = json.load(f)
    except FileNotFoundError:
        existing_data = []
    
    existing_data.append(data)
    
    with open(file, 'w') as f:
        json.dump(existing_data, f, indent=4)

def getLast_requestNum(file):
    try:
        with open(file, 'r') as f:
            data = json.load(f)
            if data:
                last_request = data[-1]
                return last_request.get('requestNum', 0) 
            else:
                return 0
    except FileNotFoundError:
        return 0

def getTime():
    current_datetime = datetime.now()
    datetime_string = current_datetime.strftime("%d-%m-%Y %H:%M:%S")

    return datetime_string


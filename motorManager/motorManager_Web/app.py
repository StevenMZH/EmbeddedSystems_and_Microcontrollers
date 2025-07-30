from flask import Flask, render_template, request
from coder import encryptData, translatePackages
from serialCOM import packagesTrasmition
from loadData import processData, printData, writeData, getLast_requestNum, getTime, Package, printPackage, readPackage

serialPort = 'COM3'
dataFile = 'process_Record.json'
packagesFile = 'packages_Record.json'

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':

        speed = request.form['Speed']
        rotation = request.form['Rotation']
        mode = request.form['Mode']
        timer_type = request.form['timerType']
        time = request.form['time']
        timer_measurements = request.form['Measurment']
        conditional_type = request.form['conditionalType']
        conditional = request.form['Conditional']

        print('\n\n')
        print('# Current Data #\n')
        print('Speed:', speed)
        print('Rotation:', rotation)
        print('Mode:', mode)
        print('Timer Type:', timer_type)
        print('Time:', time)
        print('Timer Measurements:', timer_measurements)
        print('Conditional Type:', conditional_type)
        print('Conditional:', conditional)
        print('\n')

        packages = encryptData(speed, rotation, mode, timer_type, time, timer_measurements, conditional_type, conditional)
        print('Encrypted Packages: \n',packages,'\n')
        
        if(packages != -1):
            packagesBin = translatePackages(packages)
            packagesTrasmition(packagesBin, serialPort)

            # Records
            data = processData(getLast_requestNum(dataFile)+1, getTime() , speed, rotation, mode, timer_type, time, timer_measurements, conditional_type, conditional)
            packages = Package(getLast_requestNum(dataFile)+1, getTime() , packages)
            writeData(dataFile , data.__dict__)  
            writeData(packagesFile, packages.__dict__)
            printData(dataFile)
            printPackage(packagesFile)
            print("\n\n")


    return render_template('index.html')

@app.route('/about')
def about():
    return render_template('about.html')

@app.route('/contact')
def contact():
    return render_template('contact.html')


if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')

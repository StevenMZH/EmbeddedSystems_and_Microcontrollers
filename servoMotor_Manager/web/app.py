from flask import Flask, render_template, request
from serialCOM import packagesTrasmition

serialPort = 'COM13'


app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        button1 = request.form.get('button1')
        button2 = request.form.get('button2')
        button3 = request.form.get('button3')
        button4 = request.form.get('button4')
        button5 = request.form.get('button5')


        print('\n\n')
        print('Button 1:', button1)
        print('Button 2:', button2)
        print('Button 3:', button3)
        print('Button 4:', button4)
        print('Button 5:', button5)
        print('\n')

        data = ''

        if button1:
            data = 'A'
        elif button2:
            data = 'B'
        elif button3:
            data = 'C'
        elif button4:
            data = 'D'
        elif button5:
            data = 'E'
        else:
            data = ''

        print('\n')
        print('Data: ',data)
        print('\n')

        packagesTrasmition(data, serialPort)

    return render_template('index.html')


@app.route('/about')
def about():
    return render_template('about.html')

@app.route('/contact')
def contact():
    return render_template('contact.html')

if __name__ == '__main__':
    app.run(debug=True)

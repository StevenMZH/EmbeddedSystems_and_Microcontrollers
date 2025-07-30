import json

dataFile = "jsonEx.json"

def writeData(dataFile, data):
    try:
        with open(dataFile, "r") as file:
            datos_existente = json.load(file)

    except FileNotFoundError:
        datos_existente = []

    datos_existente.append(data)

    with open(dataFile, "w") as file:
        json.dump(datos_existente, file, indent=4)

def readData(dataFile):

    with open(dataFile, "r") as file:
        datos_leidos = json.load(file)

    print("Datos en el archivo JSON:")
    for idx, data in enumerate(datos_leidos, start=1):
        print(f"Persona {idx}: {data}")


if __name__ == '__main__':

    person1 = {
        "nombre": "Maria",
        "edad": 25,
        "ciudad": "Leon"
    }

    writeData(dataFile, person1)
    readData(dataFile)



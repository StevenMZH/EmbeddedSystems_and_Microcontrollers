
# Packages of Data #
def encryptData(speed, rotation, mode, timerType, time, measurment, conditional_type, conditions):
    packages = []
    
    # Command Segment # 
    packages.append( encryptCommand(speed, rotation, mode, timerType, time, conditional_type) )

    # Time Segment # 
    if(timerType != 'desactivated' and time != '0' and time != ''):
       packages.append( encryptTime(time, measurment) )

    # Condition Segment # 
    if(conditional_type != 'none' and conditional_type != ''):
        conditionSegment = encryptConditions(conditional_type, conditions)

        if(conditionSegment == -1):
            return -1
        
        packages += conditionSegment
        
    return packages

# Comand Segment #
# (Off), (Min / Max), (Clockwise / Anti-Clockwise), (star, delta), (Desactivated / TON / TOF (2bits)), (on/off (conditions))
def encryptCommand(speed, rotation, mode, timerType, time, conditional_type):
    code = ''

    # (Off)
    if(speed == 'off'):
        return '00000000'

    # 1bit (On)
    code += '1'

    # 2bits
    if(speed == 'min'):
        code += '0'
    elif(speed == 'max'):
        code += '1'

    # 3bits
    if(rotation == 'clockwise'):
        code += '0'
    elif(rotation == 'counterClockwise'):
        code += '1'

    # 5bits
    if(mode == 'starDelta'):
        code += '11'
    elif(mode == 'star'):
        code += '10'
    elif(mode == 'delta'):
        code += '01'

    # 7bits
    if(timerType == 'Desactivated' or time == '0'):
        code += '00'
    elif(timerType == 'TON'):
        code += '10'
    elif(timerType == 'TOF'):
        code += '11'

    # 8bits
    if(conditional_type != 'none' and conditional_type != ''):
        code += '1'
    else:
        code += '0'

    return code

# Time Segment # 
 # (hour/ noHour), (min/seg), (time (6bits))
def encryptTime(time, measurment):
    code = ''

    # 2bit
    if(measurment == 'seg'):
        code += '00'
    elif(measurment == 'min'):
        code += '01'
    elif(measurment == 'hours'):
        code += '11'

    # 8bits
    bitTime = int(time) & 0b111111
    bitTime = format(bitTime, '06b')
    code += bitTime

    return code

# Conditional Segments #
# first package: all 0s if it's a 'if', else if it's a 'while' all will be 1s
# next packages: (filler (2 bits)) (nothing / not), (id (2bits)), (noLogicGates / LogicGate), ( or / and ), (finish / continue)
def encryptConditions(conditional_type, conditions):
    IDs = {'A':'00', 'B':'01', 'C':'10', 'D':'11'}
    logicGates = {'':'000', '+':'101', '*':'111'}

    packages = ['00000000']
    if(conditional_type == 'while'):
        packages[0] = '11111111'

    conditions = analyzeCondition(conditions)
    if(conditions == -1):
        return -1
    
    i = 0
    while(i < len(conditions)):
        # 2bits
        code = '00'

        # 3bits
        if(conditions[i] == '!'):
            code+='1'
            i+=1
        else:
            code+='0'
        
        # 5bits
        code += IDs[conditions[i]]
        i+=1

        # 8bits
        if(i == len(conditions)):
            code+= logicGates['']
        else:
            code += logicGates[conditions[i]]
            i+=1

        packages.append(code)
        code = ''

    return packages

# Adjust Sintaxis
def analyzeCondition(condition):
    allowedChar = ['A','B','C','D','!','+','*']
    
    condition = condition.replace(" ", "")
    condition = condition.upper()
    i = 0

    for c in condition:
        if(c not in allowedChar):
            return -1

    if(conditionTester(condition) == -1):
        return -1

    return condition

# Verify Condition
def conditionTester(condition: str):
    A, B, C, D = 1,1,1,1

    condition = condition.replace("!", " not ")
    condition = condition.replace("+", " or ")
    condition = condition.replace("*", " and ")
    print("Analyzed Condition: ",condition)
    try:
        result = eval(condition)
        print("Acepted\n")
        return 1

    except(Exception):
        print("Denied: Sintax Error\n")
        return -1

def translatePackages(packages):
    translation = []
    for package in packages:
        translation.append(int(package, 2))
    return translation

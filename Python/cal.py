import math
# ------------------------------------------------------------
# Analytic Geometry
def crossPro(a, b):
    "Calculate the cross product if the two vectors"
    assert len(a) == len(b)
    if(len(a) == 3):
        result = []
        result.append(a[1]*b[2]-a[2]*b[1])
        result.append(a[2]*b[0]-a[0]*b[2])
        result.append(a[0]*b[1]-a[1]*b[0])
        return result
    if(len(a)==2):
        result = a[0]*b[1]-a[1]*b[0];
        return result
def dotPro(a, b):
    "Calculate the dot product of two vectors"
    assert len(a) == len(b)
    result = 0
    for i in range(len(a)):
        result += a[i]*b[i]
    return result
def vectorMod(a):
    "Calculate the mod of the vector"
    result = 0
    for x in a:
        result += x**2
    return "sqrt("+str(result)+')'
def distanceDF(dot, flat):
    "Calculate the distance between the dot and the flat"
    num = 0
    deno = 0
    for i in range(len(dot)):
        num += dot[i]*flat[i]
    num += flat[-1]
    if(num < 0):
        num = -num
    for i in range(len(flat)-1):
        deno += flat[i]**2
    result = str(num) + '/sqrt(' + str(deno) + ')'
    return result
def distanceDD(dotA,dotB):
    "Calculate the distance between two dots"
    assert len(dotA) == len(dotB)
    result = 0
    for i in range(len(dotA)):
        result += (dotA[i] - dotB[i])**2
    return "sqrt(" + str(result) + ')'
def vectorCos(vecA, vecB):
    "Calculate the cosine of the two vectors"
    assert len(vecA) == len(vecB)
    return str(dotPro(vecA, vecB))+'/'+vectorMod(vecA)+'+'+vectorMod(vecB)
# ------------------------------------------------------------
# Analytic Circuit
def paraReEqual(a):
    sum = 0
    pro = 1
    for x in a:
        sum += x
        pro *= x
    return str(pro)+'/'+str(sum)
# ------------------------------------------------------------
# Physical Experiment
def aveValue(seq):
    "Calculate the average value of the value sequence"
    n = len(seq)
    sum = 0
    for x in seq:
        sum += x
    return (sum/n,str(sum)+'/'+str(n))
def UA(seq):
    n = len(seq)
    ave = aveValue(seq)[0]
    sum = 0
    for x in seq:
        sum += (x-ave)**2
    n *= n-1
    return (math.sqrt(sum/n),"sqrt("+str(sum)+'/'+str(n)+')')
def UB(instrument_deviation):
    return (instrument_deviation/math.sqrt(3),str(instrument_deviation)+"/sqrt(3)")
def Ux(UA,UB):
    return (math.sqrt(UA**2+UB**2),"sqrt("+str(UA**2+UB**2)+')')
def result(average_value,u_x):
    return str(average_value)+'±'+str(u_x)
def reDeviation(u_x,average_value):
    return u_x/average_value*100
# ------------------------------------------------------------

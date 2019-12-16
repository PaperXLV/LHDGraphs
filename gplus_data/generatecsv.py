outp = open("geom.csv", "w")
f = open("geom.net", "r")


for line in f:
    data = line.split()
    output = ""
    for x in data:
        output += x + ","
    output = output[:-1] + '\n'
    outp.write(output)

outp.close()
f.close()

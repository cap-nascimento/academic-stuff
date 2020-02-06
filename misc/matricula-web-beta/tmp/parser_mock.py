import json
import random as r

filename = input()
#codes = ["PS", "PT", "HN", "PW", "PY", "HR", "HT", "YE", "ID", "YT", "IE", "IL", "AF", "ZA", "IR", "AL", "IT", "AM", "AR", "ZM", "AU", "AW", "AZ", "BA", "RS", "BD", "RU", "BE", "BG", "JO", "JP", "BO", "SA", "SB", "BQ", "BR", "SC", "SE", "SI", "SJ", "BY", "KE", "KH", "CA", "SR", "CD", "KM", "KP", "SY", "CI", "KR", "CL", "CM", "CN", "CO", "KY", "CR", "KZ", "CU", "TG", "TH", "LA", "TJ", "CY", "CZ", "TM", "TN", "LK", "DE", "TZ", "LT", "LV", "DO", "UA", "LY", "MA", "MD", "ME", "MG", "MK", "US", "EC", "EE", "MN", "EG", "UY", "MT", "MU", "MX", "MY", "ES", "VE", "ET", "NA", "VN", "NG", "NI", "NL", "NO", "NP", "FI", "FM", "FR", "GB", "GE", "OM", "GM", "GN", "GR", "GT", "PA", "XK", "PE", "PH", "PK", "PL"]

arq = open(filename, "r")
arq2 = open("out.txt", "w")
# for line in arq:
#     obj = json.loads(line)
#     pos = 0
#     for i in range(len(codes)):
#         if(codes[i] == obj['course']):
#             pos = i
#             break
    
#     if(pos >= 0 and pos < 38):
#         obj['course'] = "CC"
#     elif(pos >= 38 and pos < 76):
#         obj['course'] = "EC"
#     elif(pos >= 76 and pos < len(codes)):
#         obj['course'] = "LC"

#     arq2.write(obj['nome'] + ";" + str(obj['code']+1000) + ";" +
#     obj['course'] + ";;;;\n")

arr = []
for line in arq:
    arr.append(line)

qt = 0
indexes = []
while(qt < len(arr)):
    n = r.randrange(len(arr))
    has = False
    for p in indexes:
        if n == p:
            has = True
            break
    if not has:
        indexes.append(n)
        qt+=1

for i in range(len(indexes)):
    arq2.write(arr[indexes[i]])

# for line in arr:
#     sp = line.split(';')
#     if(len(sp[4])!=0):
#         x = int(sp[4])
#         x /= 100.0
#         print(sp[4])
#         arq2.write(sp[0] + ';' + sp[1] + ';' + sp[2] + ';' + sp[3] + ';' + str(x) + ';' + sp[5] + ';' + sp[6])
#     else:
#         arq2.write(line)

arq.close()
arq2.close()
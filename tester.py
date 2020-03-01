import random
import string
f = open("somefile", "w");
#f.write("".join(str(random.randint(-100,1000)) +" ,  " for _ in range(1000)))
f.write("".join((''.join(random.choice(string.ascii_lowercase + '\n') for _ in range(random.randint(0,10)))) +" ,  " for _ in range(100)))
f.close()

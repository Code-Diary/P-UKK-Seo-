n = 0
k = 0
hex_str = ""
 
def main () :
    t = int(input())
    for i in range (t) :
        input_()
        solve (i+1)
 
 
def input_ () :
    global n, k, hex_str
    n, k = [int(item) for item in input().split()]
    n //= 4
    hex_str = input ()
 
def solve (testcase) :
    global n, k, hex_str
    doubled_hex = hex_str*2
    all_case = []
    for i in range(len(hex_str)) :
        all_case.append(doubled_hex[i:i+n])
    int_all_case = [int(item, 16) for item in all_case]
    int_all_case = list(set(int_all_case))
    int_all_case.sort(reverse=True)
    print("#%d" % testcase,int_all_case[k-1])
 
main ()

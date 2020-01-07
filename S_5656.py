from functools import reduce
from copy import deepcopy

n = 0
w = 0
h = 0
arr = []

def main () :
	t = int(input())
	for i in range (t) :
		input_()
		solve (i)

def input_ () :
	global n, w, h, arr
	n, w, h = [int(item) for item in input().split()]
	before_transposed = [[int(i) for i in input().split()] for j in range(h)]
	transposed = [list(row) for row in zip(*before_transposed)]
	for i in range (len(transposed)) :
		transposed[i].reverse()
	arr = transposed

def get_pos(row, boom_box) :
	for idx in range (len(boom_box[row])-1, -1, -1) :
		if not boom_box[row][idx] == 0 :
			return row, idx
	return row, -1

def is_safe (row, col) :
	global w, h
	return 0 <= row < w and 0 <= col < h

def boom_chain(row, col, boom_box) :
	size = boom_box[row][col]
	boom_box[row][col] = 0
	direction = [(0, 1), (0, -1), (1, 0), (-1, 0)]
	adjacent = []
	for dist in range(1, size) :
		for d in direction :
			pos = (row+d[0]*dist, col+d[1]*dist)
			if is_safe (*pos) :
				adjacent.append(pos)
	result = boom_box
	for adj in adjacent :
		result = boom_chain(adj[0], adj[1], result)
	return result

def make_zero_back (row_list) :
	row_size = len(row_list)
	non_zero = []
	for item in row_list :
		if not item == 0 :
			non_zero.append(item)
	non_zero += [0]*(row_size-len(non_zero))
	return non_zero

def boom (row, boom_box) :
	row, col = get_pos(row, boom_box)
	if is_safe (row, col):
		result = boom_chain(row, col, boom_box)
	else :
		result = boom_box
	for row in range (len(result)) :
		result[row] = make_zero_back(result[row])
	return result

def cnt_blocks (boom_box) :
	cnt = 0
	for row in boom_box :
		for col in row :
			if not col == 0 :
				cnt += 1
	return cnt
def print_boom_box(boom_box) :
	for i in boom_box :
		for j in i :
			print(j, end=" ")
		print("")

def traversal(row, depth, limit, boom_box) :
	global sol
	if depth == limit :
		sol = min(sol, cnt_blocks(boom_box))
	else :
		for row_idx in range(len(boom_box)) :
			next_boom_box = boom(row_idx, deepcopy(boom_box))
			traversal(row_idx, depth+1, limit, next_boom_box)

def solve (testcase) :
	global sol
	global n, arr 
	sol = 1000000000000
	traversal(-1, 0, n, deepcopy(arr))
	print("#%d" % (testcase+1), sol)

main ()


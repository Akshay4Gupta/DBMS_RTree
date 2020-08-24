import sys
import random

# 0 - insert 1 - query 2 - insert+query

inserted_elements = []
not_inserted = []
def main(dimension, BULKLOAD, total, bulkloadfilename, resfilename):
	f = open(bulkloadfilename,'w')
	for i in range(BULKLOAD):
		insert_element = []
		for j in range(1,dimension+1):
			# print(i*j+j+1000000, end = ' ')
			f.write(str(i*j+j+1000000) + " ")
			insert_element.append(i*j+j+1000000)
		inserted_elements.append(insert_element)
		f.write("\n")
		# print("")
	f.close()

	f = open(resfilename,'w')
	f.write("BULKLOAD\n\n\n")
	print("BULKLOAD Testcases/selfTC_3/bulkload.txt")
	for i in range(2*total):
		insert_element = []
		for j in range(dimension):
			num = random.randrange(100000, 1e8,1)
			insert_element.append(num)

		mode = random.randrange(0,3)
		ranchoice = random.randrange(0,2)
		if mode == 0 or mode == 2:
			inserted_elements.append(insert_element)
		else:
			not_inserted.append(insert_element)
		if mode == 0 or mode == 2:
			print("INSERT ", end = " ")
			for j in insert_element:
				print(j, end=" ")
			print("")
			f.write("INSERT\n\n\n")
		if mode == 2:
			print("QUERY ", end = " ")
			for j in insert_element:
				print(j, end=" ")
			print("")
			f.write("TRUE\n\n\n")
		if mode == 1:
			if ranchoice == 0:
				insert_element = random.choice(inserted_elements)
				print("QUERY ", end = " ")
				for j in insert_element:
					print(j, end=" ")
				print("")
				f.write("TRUE\n\n\n")
			else:
				insert_element = random.choice(not_inserted)
				print("QUERY ", end = " ")
				for j in insert_element:
					print(j, end=" ")
				print("")
				f.write("FALSE\n\n\n")
	f.close()


main(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]), sys.argv[4], sys.argv[5])

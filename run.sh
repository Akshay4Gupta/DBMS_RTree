# Build
make

# # #
# # Test case 1
# time timeout 300 ./rtree Testcases/TC_1/queries_2_10_100_100.txt 10 2 output_tc1.txt
# cmp --silent output_tc1.txt Testcases/TC_1/answer_2_10_100_100.txt && echo 'TC1: SUCCESS' || echo 'TC1: FAILED'
# diff output_tc1.txt Testcases/TC_1/answer_2_10_100_100.txt | grep '^>' | wc -l
# # rm -f temp.txt
# #
# # Test case 2
# time timeout 300 ./rtree Testcases/TC_2/queries_2_10_100_1000.txt 10 2 output_tc2.txt
# cmp --silent output_tc2.txt Testcases/TC_2/answer_2_10_100_1000.txt && echo 'TC2: SUCCESS' || echo 'TC2: FAILED'
# diff output_tc2.txt Testcases/TC_2/answer_2_10_100_1000.txt | grep '^>' | wc -l
# # rm -f temp.txt
# #
# # # Test case 3
# time timeout 300 ./rtree Testcases/TC_3/queries_3_10_1000_10000.txt 10 3 output_tc3.txt
# cmp --silent output_tc3.txt Testcases/TC_3/answer_3_10_1000_10000.txt && echo 'TC3: SUCCESS' || echo 'TC3: FAILED'
# diff output_tc3.txt Testcases/TC_3/answer_3_10_1000_10000.txt | grep '^>' | wc -l
# # rm -f temp.txt
# #
# # # Test case 4
# time timeout 300 ./rtree Testcases/TC_4/queries_5_20_1000_1000.txt 20 5 output_tc4.txt
# cmp --silent output_tc4.txt Testcases/TC_4/answer_5_20_1000_1000.txt && echo 'TC4: SUCCESS' || echo 'TC4: FAILED'
# diff output_tc4.txt Testcases/TC_4/answer_5_20_1000_1000.txt | grep '^>' | wc -l
# # rm -f temp.txt
# #
# # # Test case 5
# time timeout 300 ./rtree Testcases/TC_5/queries_2_10_100000_100000.txt 10 2 output_tc5.txt
# cmp --silent output_tc5.txt Testcases/TC_5/answer_2_10_100000_100000.txt && echo 'TC5: SUCCESS' || echo 'TC5: FAILED'
# diff output_tc5.txt Testcases/TC_5/answer_2_10_100000_100000.txt | grep '^>' | wc -l
# # rm -f temp.txt
# #
# # # # Test case 6
# # time timeout 300 ./rtree Testcases/TC_6/queries_2_10_100_100.txt 10 2 output_tc6.txt
# # cmp --silent output_tc1.txt Testcases/TC_6/answer_2_10_100_100_bulk.txt && echo 'TC6: SUCCESS' || echo 'TC6: FAILED'
# # diff output_tc6.txt Testcases/TC_6/answer_2_10_100_100_bulk.txt | grep '^>' | wc -l
# # # rm -f temp.txt
# # #
# # # # Test case 7
# # time timeout 300 ./rtree Testcases/TC_7/queries_2_10_100_100.txt 10 2 output_tc7.txt
# # cmp --silent output_tc1.txt Testcases/TC_7/answer_2_10_100_100_insert.txt && echo 'TC7: SUCCESS' || echo 'TC7: FAILED'
# # diff output_tc7.txt Testcases/TC_7/answer_2_10_100_100_insert.txt | grep '^>' | wc -l
# # # rm -f temp.txt

# # Test case 8
time timeout 300 ./rtree Testcases/selfTC_1/queries.txt 7 5 output_tc8.txt
cmp --silent output_tc8.txt Testcases/selfTC_1/answer.txt && echo 'TC8: SUCCESS' || echo 'TC8: FAILED'
diff output_tc8.txt Testcases/selfTC_1/answer.txt | grep '^>' | wc -l
rm -f temp.txt

# time ./rtree Testcases/selfTC_2/queries.txt 500 10 output_tc9.txt
# cmp --silent output_tc9.txt Testcases/selfTC_2/answer.txt && echo 'TC9: SUCCESS' || echo 'TC9: FAILED'
# diff output_tc9.txt Testcases/selfTC_2/answer.txt | grep '^>' | wc -l
# rm -f temp.txt

# time timeout 300 ./rtree Testcases/selfTC_2/queries.txt 50 10 output_tc10.txt
# cmp --silent output_tc10.txt Testcases/selfTC_2/answer.txt && echo 'TC10: SUCCESS' || echo 'TC10: FAILED'
# diff output_tc10.txt Testcases/selfTC_2/answer.txt | grep '^>' | wc -l
# rm -f temp.txt
#
# time timeout 300 ./rtree Testcases/selfTC_2/queries.txt 100 10 output_tc11.txt
# cmp --silent output_tc11.txt Testcases/selfTC_2/answer.txt && echo 'TC11: SUCCESS' || echo 'TC11: FAILED'
# diff output_tc11.txt Testcases/selfTC_2/answer.txt | grep '^>' | wc -l
# rm -f temp.txt

make clean
rm output_tc?.txt

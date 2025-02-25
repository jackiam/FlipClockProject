Test 1. 200 steps, 1 second delay. Over 12 (simulated) hours 100% accuracy

Test 2. 17 steps, 1 second delay. Over 1 (simulated) hour, gained 1 minute. I believe this error will be additive.

Test 3. 16 steps. 1 second delay.  Over 1 (simulated) hour, lost 2 minutes. I believe this error will 
be additive.

Test 4. Because the actual step size should be 16.666…, let's multiply times 3, run 3 minutes per step. 50 steps. This should solve accuracy.

Result 4. 100% accuracy over 3 (simulated) hours


In between tests the code got nasty and ugly. Erased everything, started over now testing time in 1 (simulated) hour increments. Seems to be working properly for 1000 steps.

Test 5. 50 steps are required for 3 minutes, I can achieve minute accuracy if for 2 sets of steps, the steps are equal to 16, for the third there will be 18 steps. This is a total of 50 steps per 3 which should result in smooth motion and no loss or gain of time

Result 5. 8+ (simulated) hours of 100% accuracy, waiting for more testing


Various tests and tweaks went un-documented. The current I'm going to say is test 12.

Test 12. Adjusted if statements to properly adjust the time. Steps and count will be changed in future tests, but this test includes the step variable amounts from the previous test. Real 1 hr test start at 12:30 pm. 

Result 12. At 1:30 pm, the clock lost 1 minute over the hour.

Test 13. Add 1 additional minute (16 steps) to the end of each hour. This should fix the issue. 
Test started at 1:35 pm.

Result 13. 




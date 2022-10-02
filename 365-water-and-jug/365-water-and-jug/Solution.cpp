//
//  Solution.cpp
//  365-water-and-jug
//
//  Created by Derek Harrison on 02/10/2022.
//

#include <stdio.h>

class Solution {
    long gcd_rec(long a, long b) {
        long res = -1;

        if(a == 0)
            res = b;

        if(a > 0)
            res = gcd_rec(b % a, a);

        return res;
    }

    long gcd(long a, long b) {

        return a < b ? gcd_rec(a, b) : gcd_rec(b, a);
    }
    
public:
    bool canMeasureWater(int jug1Capacity, int jug2Capacity, int targetCapacity) {
        
        if(jug1Capacity + jug2Capacity < targetCapacity) {
            return false;
        }
        
        if(targetCapacity % jug1Capacity == 0 || targetCapacity % jug2Capacity == 0) {
            return true;
        }
        
        return gcd(jug1Capacity, jug2Capacity) == 1;
    }
};

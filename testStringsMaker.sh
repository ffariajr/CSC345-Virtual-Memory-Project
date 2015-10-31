#! /bin/bash

./refstr -o strings.ref w -refSize 50 -pageLimit 20 random
./refstr -o strings.ref a -refSize 200 -pageLimit 50 spatial
./refstr -o strings.ref a -refSize 200 -pageLimit 50 temporal
./refstr -o strings.ref a -refSize 500 -pageLimit 100 both


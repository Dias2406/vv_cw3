#include <stdio.h>
#include <stdlib.h>

// Function to calculate the greatest common divisor
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Function to compute the maximum number of points on the same line
int maxPoints(int** points, int pointsSize, int* pointsColSize) {
    if (pointsSize <= 2) return pointsSize;
    
    int maxPoints = 0;

    // Iterate over each point to use it as an anchor
    for (int i = 0; i < pointsSize; i++) {
        int maxLocal = 0, overlap = 0, vertical = 0;
        struct Slope {
            int dy;
            int dx;
            int count;
        } *slopes = malloc(sizeof(struct Slope) * pointsSize);
        int slopesSize = 0;

        for (int j = i + 1; j < pointsSize; j++) {
            int dx = points[j][0] - points[i][0];
            int dy = points[j][1] - points[i][1];
            
            if (dx == 0 && dy == 0) {
                overlap++;
                continue;
            }

            if (dx == 0) {
                vertical++;
                continue;
            }

            int g = gcd(dx, dy);
            dy /= g;
            dx /= g;
            
            if (dx < 0) {
                dx = -dx;
                dy = -dy;
            }

            int found = 0;
            for (int k = 0; k < slopesSize; k++) {
                if (slopes[k].dy == dy && slopes[k].dx == dx) {
                    slopes[k].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                slopes[slopesSize].dy = dy;
                slopes[slopesSize].dx = dx;
                slopes[slopesSize].count = 1;
                slopesSize++;
            }
        }

        for (int k = 0; k < slopesSize; k++) {
            if (slopes[k].count > maxLocal) {
                maxLocal = slopes[k].count;
            }
        }
        
        maxLocal = (vertical > maxLocal ? vertical : maxLocal) + overlap + 1;
        maxPoints = (maxLocal > maxPoints ? maxLocal : maxPoints);
        free(slopes);
    }
    
    return maxPoints;
}

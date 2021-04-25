#include <stdio.h>
#include <string.h>
#include <math.h>

#define pi 3.142
const int R1 = 1, R2 = 2, K2 = 4;
const float thetaSpacing = 0.07, phiSpacing = 0.02;
const int screen_width = 160;
const int screen_height = 35;

int k;
double sin(), cos();

void renderTorus(const float A, const float B)
{
}

main()
{
    float A = 0, B = 0, phi, theta, z[screen_height * screen_width];
    char b[screen_height * screen_width];
    printf("\x1b[2J");
    for (;;)
    {
        memset(b, 32, sizeof(b[0]) * screen_height * screen_width);
        memset(z, 0, sizeof(z[0]) * screen_height * screen_width);
        float sinA = sin(A), cosA = cos(A), cosB = cos(B), sinB = sin(B);

        for (theta = 0; 2 * pi > theta; theta += thetaSpacing)
        {
            float sintheta = sin(theta), costheta = cos(theta);
            for (phi = 0; 2 * pi > phi; phi += phiSpacing)
            {
                float sinphi = sin(phi),
                      cosphi = cos(phi),
                      circley = sintheta * R1,
                      circlex = (costheta * R1) + R2,
                      mess = 1 / (sinphi * circlex * sinA + circley * cosA + K2),
                      t = sinphi * circlex * cosA - circley * sinA;
                int x = (screen_width / 2) + 30 * mess * (cosphi * circlex * cosB - t * sinB),
                    y = (screen_height / 2) + 15 * mess * (cosphi * circlex * sinB + t * cosB),
                    o = x + screen_width * y,
                    N = 8 * ((circley * sinA - sinphi * costheta * cosA) * cosB - sinphi * costheta * sinA - sintheta * cosA - cosphi * costheta * sinB);
                if (screen_height > y && y > 0 && x > 0 && screen_width > x && mess > z[o])
                {
                    z[o] = mess;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        printf("\x1b[d");
        for (k = 0; k <= screen_width * screen_height; k++)
            putchar(k % screen_width ? b[k] : '\n');
        A += 0.04;
        B += 0.02;
        for (k = 0; k < 10000000; k++)
            ;
    }
}

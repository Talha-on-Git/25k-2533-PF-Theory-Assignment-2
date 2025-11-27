#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void calculateFuel(float fuel, float consumption, int recharge, int solarBonus, int planet, int totalPlanets, int specialZone)
{
    if (planet > totalPlanets)
    {
        printf("\n\nJourney completed!");
        printf("\nremaining fuel = %.2f", fuel);
        return;
    }

    if (planet == specialZone)
    {
        printf("\n\nSpecial zone (planet %d) reached!, you will get bonus recharge!", planet);
        fuel += recharge;
    }

    if ((planet % 4) == 0)
    {
        printf("\n\nplanet %d reached!, you will get solar bonus!", planet);
        fuel += solarBonus;
    }
    fuel -= consumption;

    if (fuel <= 0)
    {
        fuel = 0;
        printf("\nPlanet %d: Remaining Fuel = %.2f", planet, fuel);
        printf("\n\nOut of fuel at planet %d!, Journey cannot be completed", planet);
        return;
    }
    printf("\nPlanet %d: Remaining Fuel = %.2f", planet, fuel);
    planet++;

    calculateFuel(fuel, consumption, recharge, solarBonus, planet, totalPlanets, specialZone);
}
int main()
{
    int totalPlanets, recharge, solarBonus;
    float fuel, consumption;

    printf("\nEnter the total number of planets: ");
    scanf("%d", &totalPlanets);
    printf("\nEnter the fuel: ");
    scanf("%f", &fuel);
    // printf("\nEnter the recharge: ");
    // scanf("%d", &recharge);
    // printf("\nEnter the solar bonus that spaceship gets: ");
    // scanf("%d", &solarBonus);

    srand(time(NULL));
    int specialZone = (rand() % totalPlanets) + 1;
    if (totalPlanets > 6)
    {
        recharge = 50;
        solarBonus = 100;
        consumption = (fuel / totalPlanets) + 60;
        printf("\nConsumption: %.2f, Recharge: %d, Solar Bonus: %d", consumption, recharge, solarBonus);
    }
    else
    {
        recharge = 10;
        solarBonus = 50;
        consumption = (fuel / totalPlanets)+20;
         printf("\nConsumption: %.2f, Recharge: %d, Solar Bonus: %d", consumption, recharge, solarBonus);
    }

    printf("\nSpecial gravitational zone is at Planet %d\n", specialZone);

    calculateFuel(fuel, consumption, recharge, solarBonus, 1, totalPlanets, specialZone);
    return 0;
}
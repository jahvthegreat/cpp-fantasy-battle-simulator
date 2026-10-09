#include <cassert>
#include "barbarian.h"
#include "health.h"
#include "abilities.h"
#include "weapons.h"

int main() {
    using namespace seneca;
    Barbarian<double, Bersek, Sword> regular("Regular", 100, 20, 0, Sword{}, Sword{});
    assert(regular.getHealthMax() == 100 && regular.getHealth() == 100);
    regular.takeDamage(25);
    assert(regular.getHealth() == 75 && regular.getHealthMax() == 100);
    regular.setHealth(90);
    assert(regular.getHealth() == 90 && regular.getHealthMax() == 100);
    regular.setHealthMax(200);
    assert(regular.getHealth() == 200 && regular.getHealthMax() == 200);

    Barbarian<SuperHealth, Bersek, Sword> resilient("Resilient", 100, 20, 0, Sword{}, Sword{});
    resilient.takeDamage(20);
    assert(resilient.getHealth() == 90 && resilient.getHealthMax() == 100);

    Barbarian<InfiniteHealth, Bersek, Sword> immortal("Immortal", 100, 20, 0, Sword{}, Sword{});
    immortal.takeDamage(100000);
    assert(immortal.isAlive() && immortal.getHealthMax() == 100);
    return 0;
}

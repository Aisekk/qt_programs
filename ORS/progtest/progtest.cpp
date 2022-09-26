#include <stdio.h>
#include <string.h>

typedef char	Carrier[3];		// код авиакомпании
typedef char	FlightNo[5];	// номер рейса
typedef char	Point[4];		// код пункта
typedef long	Fare;				// тариф

// Пункт маршрута
struct RoutePoint {
    RoutePoint	*next;
    Point			point;

    RoutePoint() : next(0) {}
};

// Маршрут
class Route {
    RoutePoint	*first;

public:
    Route();
    ~Route();

    // чтение из файла
    int read(const char *fileName);	// 0 - OK, !=0 - ошибка

    // проверка маршрута на:
    //   несовпадение соседних пунктов
    //   не менее двух пунктов в маршруте
    int check() const;	// 0 - OK, !=0 - ошибка

    // итератор
    RoutePoint	*iterator(RoutePoint *& iter) const;

    // печать на stdout
    void print(const char *prefix) const;
};

// Рейс
struct Flight {
    Carrier	carrier;		// перевозчик
    FlightNo	flightNo;	// номер рейса
    Point		depPoint;	// пункт отправления
    Point		arrPoint;	// пункт назначения
    Fare		fare;			// тариф

    void	print() const;
};

//
class ScheduleItem : public Flight {
    friend class Schedule;

    ScheduleItem	*next;

public:
    ScheduleItem() : next(0) {}
};

// Расписание
class Schedule {
    ScheduleItem	*firstFlight;
public:
    Schedule();
    ~Schedule();

    // чтение из файла
    int read(const char *fileName);	// 0 - OK, !=0 - ошибка

    // итератор
    ScheduleItem	*iterator(ScheduleItem *& iter) const;

    // печать на stdout
    void	print() const;

};

// Участок перевозки
struct TransLeg {
    TransLeg	*next;
    Flight	flight;

    TransLeg() : next(0) {}
};

// Перевозка
class Transportation {
    TransLeg	*firstLeg;
public:
    Transportation();
    ~Transportation();

    void	flush();
    int	buildCheapest(const Route & route, const Schedule & schedule);
    void	print() const;

private:
    Flight	*findCheapestFlight(const Schedule & schedule, const char *depPoint, const char *arrPoint);
};

//___ Реализация _________________________________

//___ Route ______________________________________

Route::Route()
    : first(0)
{
}

Route::~Route()
{
    for (RoutePoint *item = first; item; ) {
        RoutePoint	*toDelete = item;
        item = item->next;
        delete toDelete;
    }
}

int Route::read(const char *fileName)
{
    RoutePoint	*lastItem = 0;

    FILE	*f = fopen(fileName, "r");
    if (!f) return 1;

    Point	readPoint;
    while (fscanf(f, "%3s", readPoint) == 1) {
        RoutePoint	*newItem = new RoutePoint;
        strcpy(newItem->point, readPoint);
        if (lastItem) {
            lastItem->next = newItem;
        }
        else
            first = newItem;
        lastItem = newItem;
    }

    fclose(f);
    return 0;
}

int Route::check() const
{
    if (!first || !first->next)
        return 1;

    RoutePoint	*iter = 0;
    while (iterator(iter)) {
        if (iter->next && 0 == strcmp(iter->point, iter->next->point))
            return 1;
    }
    return 0;
}

RoutePoint * Route::iterator(RoutePoint *& iter) const
{
    if (iter)
        iter = iter->next;
    else
        iter = first;
    return iter;
}

void Route::print(const char *prefix) const
{
    if (prefix)
        printf(prefix);

    RoutePoint	*iter = 0;
    while (iterator(iter)) {
        printf("%s ", iter->point);
    }

    printf("\n");
}

//___ Расписание ___________________________________________

void Flight::print() const
{
    printf("%-2s %-4s %-3s %-3s %10ld",
        carrier,
        flightNo,
        depPoint,
        arrPoint,
        fare);
}

Schedule::Schedule()
    : firstFlight(0)
{
}

Schedule::~Schedule()
{
    for (ScheduleItem *flight = firstFlight; flight; ) {
        ScheduleItem	*toDelete = flight;
        flight = flight->next;
        delete toDelete;
    }
}

int Schedule::read(const char *fileName)
{
    ScheduleItem	*lastFlight = 0;

    FILE	*f = fopen(fileName, "r");
    if (!f) return 1;

    Flight	fl;
    while (fscanf(f, "%2s %4s %3s %3s %ld", fl.carrier, fl.flightNo, fl.depPoint, fl.arrPoint, &fl.fare) == 5) {
        ScheduleItem	*newFlight = new ScheduleItem;
        *(Flight*)newFlight = fl;
        if (lastFlight) {
            lastFlight->next = newFlight;
        }
        else
            firstFlight = newFlight;
        lastFlight = newFlight;
    }

    fclose(f);
    return 0;
}

ScheduleItem * Schedule::iterator(ScheduleItem *& iter) const
{
    if (iter)
        iter = iter->next;
    else
        iter = firstFlight;
    return iter;
}

void Schedule::print() const
{
    ScheduleItem	*f = 0;
    while (iterator(f)) {
        f->print();
        printf("\n");
    }
}

//___ Transportation ______________________________________________

Transportation::Transportation()
    : firstLeg(0)
{
}

Transportation::~Transportation()
{
    flush();
}

void Transportation::flush()
{
    for (TransLeg *leg = firstLeg; leg; ) {
        TransLeg	*toDelete = leg;
        leg = leg->next;
        delete toDelete;
    }
    firstLeg = 0;
}

Flight * Transportation::findCheapestFlight(const Schedule & schedule, const char *depPoint, const char *arrPoint)
{
    Flight	*flightWithMinimalFare = 0;

    ScheduleItem	*schedItem = 0;
    while (schedule.iterator(schedItem)) {
        if (0 != strcmp(schedItem->depPoint, depPoint) ||
            0 != strcmp(schedItem->arrPoint, arrPoint)) continue;
        if (!flightWithMinimalFare || flightWithMinimalFare->fare > schedItem->fare) {
            flightWithMinimalFare = schedItem;
        }
    }

    return flightWithMinimalFare;
}

int Transportation::buildCheapest(const Route & route, const Schedule & schedule)
{
    flush();

    TransLeg	*lastLeg = 0;

    RoutePoint	*routePoint = 0;
    while (route.iterator(routePoint) && routePoint->next) {
        Flight *cheapestFlight = findCheapestFlight(schedule, routePoint->point, routePoint->next->point);
        if (!cheapestFlight) return 1;

        TransLeg	*newLeg = new TransLeg;
        newLeg->flight = *cheapestFlight;

        if (lastLeg)
            lastLeg->next = newLeg;
        else
            firstLeg = newLeg;

        lastLeg = newLeg;
    }
    return 0;
}

void Transportation::print() const
{
    int	legNo = 0;
    Fare	totalFare = 0;
    Carrier lastCarrier = "\0";
    bool allTransByOneCarrier = true;
    for (TransLeg *leg = firstLeg; leg; leg = leg->next) {
        totalFare += leg->flight.fare;
        strcpy(lastCarrier, leg->flight.carrier);
        allTransByOneCarrier &= (0 == strcmp(leg->flight.carrier, lastCarrier)) ? true : false;
        printf("% 2d: ", legNo++);
        leg->flight.print();
        printf("\n");
    }
    if (legNo > 1 && allTransByOneCarrier)
        totalFare *= 0.8;
    printf("Total fare: %ld\n", totalFare);
}


//___

int main()
{
    // читаем маршрут
    Route	route;
    if (route.read("route.txt")) {
        fprintf(stderr, "cannot read route\n");
        return 1;
    }
    route.print("Route read: ");
    if (route.check()) {
        fprintf(stderr, "route is invalid\n");
        return 1;
    }

    // читаем расписание
    Schedule	schedule;
    if (schedule.read("schedule.txt")) {
        fprintf(stderr, "cannot read schedule\n");
        return 1;
    }
    printf("\nSchedule read:\n");
    schedule.print();

    // Строим перевозку
    Transportation	trans;
    if (trans.buildCheapest(route, schedule)) {
        fprintf(stderr, "cannot build transportation\n");
        return 1;
    }

    printf("\nCheapest transportation:\n");
    trans.print();

    return 0;
}


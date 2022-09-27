#include <stdio.h>
#include <string.h>
#include <memory>

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


struct CarrierNode {
    CarrierNode	*next;
    Carrier carrier;

    CarrierNode() : next(0) {}
};

// Авиакомпании
class Carriers
{
    friend class Transportation;
    CarrierNode *firstCarrier;
public:
    Carriers();
    ~Carriers();
    void	flush();
    CarrierNode* iterator(CarrierNode*& iter) const;
};

// Перевозка
class Transportation {
    TransLeg	*firstLeg;
public:
    Transportation();
    ~Transportation();
    Transportation(Transportation&& other);
    Transportation& operator=(Transportation&& other);

    void	flush();
    int	buildCheapest(const Route & route, const Schedule & schedule);
    void	print() const;
    
    TransLeg* iterator(TransLeg*& iter) const;

    bool Empty() const;
    int Length() const;
    bool IsUnique() const;
    int TotalFare() const;

private:
    Flight* findCheapestFlight(const Schedule & schedule, const char *depPoint, const char *arrPoint);

    /// Находит все авиакомпании в расписании.
    Carriers* findAllCarriers(const Schedule& schedule);

    /// Рассчитывает рейс с уникальным перевозчиком (если есть).
    Flight*	findOneCarrierFlight(const Schedule& schedule, const char *depPoint, const char *arrPoint, Carrier carrier);

    const double coef = 0.8;
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

//___ Авиакомпании ______________________________________________

Carriers::Carriers()
    : firstCarrier(0)
{
}

Carriers::~Carriers()
{
    flush();
}

void Carriers::flush()
{
    for (CarrierNode *node = firstCarrier; node; ) {
        CarrierNode	*toDelete = node;
        node = node->next;
        delete toDelete;
    }
    firstCarrier = 0;
}

CarrierNode* Carriers::iterator(CarrierNode*& iter) const
{
    if (iter)
        iter = iter->next;
    else
        iter = firstCarrier;
    return iter;
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

Transportation::Transportation(Transportation&& other)
{
    if (other.firstLeg && this != &other)
    {
        firstLeg = other.firstLeg;
        other.firstLeg = nullptr;
    }
}

Transportation& Transportation::operator=(Transportation&& other)
{
    if (other.firstLeg && this != &other)
    {
        flush();
        firstLeg = other.firstLeg;
        other.firstLeg = nullptr;
    }
    return *this;
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

TransLeg* Transportation::iterator(TransLeg*& iter) const
{
    if (iter)
        iter = iter->next;
    else
        iter = firstLeg;
    return iter;
}

int Transportation::Length() const
{
    if (!firstLeg)
        return 0;
    int length = 0;
    for (TransLeg *leg = firstLeg; leg; leg = leg->next) {
        length++;
    }
    return length;
}

bool Transportation::Empty() const
{
    if (firstLeg)
        return false;
    return true;
}

bool Transportation::IsUnique() const
{
    bool uniq = true;
    TransLeg* leg = 0;
    iterator(leg);
    while (leg)
    {
        TransLeg* leg1 = leg;
        if (TransLeg* leg2 = iterator(leg))
        {
            uniq &= (0 == strcmp(leg1->flight.carrier, leg2->flight.carrier)) ? true : false;
            leg = leg2;
        }
    }
    return uniq;
}

int Transportation::TotalFare() const
{
    if (!firstLeg)
        return -1;
    int totalFare = 0;
    for (TransLeg *leg = firstLeg; leg; leg = leg->next) {
        totalFare += leg->flight.fare;
    }
    if (IsUnique() && Length() > 1)
    {
        totalFare *= coef;
    }
    return totalFare;
}

Flight * Transportation::findCheapestFlight(const Schedule& schedule, const char *depPoint, const char *arrPoint)
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

Carriers* Transportation::findAllCarriers(const Schedule& schedule)
{
    Carriers* carriers = new Carriers;

    ScheduleItem	*schedItem = 0;
    Carrier lastCarrier = "\0";
    CarrierNode	*lastNode = 0;
    while (schedule.iterator(schedItem))
    {
        if (0 != strcmp(schedItem->carrier, lastCarrier))
        {
            CarrierNode	*newNode = new CarrierNode;
            strcpy(newNode->carrier, schedItem->carrier);

            if (lastNode)
                lastNode->next = newNode;
            else
                carriers->firstCarrier = newNode;

            lastNode = newNode;
        }
        strcpy(lastCarrier, schedItem->carrier);
    }

    return carriers;
}

Flight* Transportation::findOneCarrierFlight(const Schedule& schedule, const char* depPoint, const char* arrPoint, Carrier carrier)
{
    Flight* flight = 0;

    ScheduleItem	*schedItem = 0;
    while (schedule.iterator(schedItem)) 
    {
        if (0 != strcmp(schedItem->carrier, carrier))
            continue;
        if (0 != strcmp(schedItem->depPoint, depPoint) ||
            0 != strcmp(schedItem->arrPoint, arrPoint)) continue;

        flight = (Flight*)schedItem;
    }

    return flight;
}

int Transportation::buildCheapest(const Route & route, const Schedule & schedule)
{
    flush();

    TransLeg	*lastLeg = 0;

    RoutePoint	*routePoint = 0;
    while (route.iterator(routePoint) && routePoint->next) 
    {
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

    if (!IsUnique())
    {
        std::unique_ptr<Carriers> carriers(findAllCarriers(schedule));
        CarrierNode* node = 0;
        while (carriers->iterator(node))
        {
            Transportation trans;
            routePoint = 0;
            lastLeg = 0;
            while (route.iterator(routePoint) && routePoint->next)
            {
                auto flight = findOneCarrierFlight(schedule, routePoint->point, routePoint->next->point, node->carrier);
                if (flight)
                {
                    TransLeg* newLeg = new TransLeg;
                    newLeg->flight = *flight;

                    if (lastLeg)
                        lastLeg->next = newLeg;
                    else
                        trans.firstLeg = newLeg;

                    lastLeg = newLeg;
                }
            }

            if (trans.Empty())
                continue;

            if (trans.Length() == Length() && trans.TotalFare() < TotalFare())
            {
                *this = std::move(trans);
            }
        }
    }

    return 0;
}



void Transportation::print() const
{
    int	legNo = 0;
    for (TransLeg *leg = firstLeg; leg; leg = leg->next) {
        printf("% 2d: ", legNo++);
        leg->flight.print();
        printf("\n");
    }
    printf("Total fare: %ld\n", TotalFare());
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



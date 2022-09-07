
//Хеш-функции для целочисленных ключей
int hashM(int key, int M){ return key % M; }
int hashA(int key, int M){ return key & (M-1); }
//Хеш-функция для строковых ключей
int hashS(char *key, int M)
{
    int h = 0, a = 127; //метод Горнера
    for(; *key != '\0'; key++) h = (a*h + *key) % M;
    return h;
}
//Универсальная хеш-функция для строковых ключей
int hashU(char *key, int M)
{
    int h, a = 31415, b = 27183;
    for(h = 0; *key != '\0'; key++, a = a*b % (M-1)) h = (a*h + *key) % M;
    return (h < 0) ? (h + M) : h;
}

#pragma GCC optimize(2)
#pragma GCC optimize(3)

#include <stdio.h>
// #include <time.h>
#define ui unsigned int
#define uc unsigned char
uc art[7000010], sw[7000010];
ui end[260];
ui ascii[260] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
ui alpha[260] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
struct node
{
    ui cnt;
    ui nxt[26];
} trie[3000010];
ui tot = 0;
struct sentence
{
    uc *st, *ed;
} s[300010];
ui word[7000010];
ui tots = 0;
ui bas[300010][20], bas_cnt[300010];
uc buffer[700010];
ui tot3 = 0;
int read()
{
    register int q = 0;
    register char c = getchar();
    while (c >= '0' && c <= '9')
        q = (q << 3) + (q << 1) + (c ^ 48),
        c = getchar();
    return q;
}
void print(ui x)
{
    if (x > 9)
        print(x / 10);
    buffer[++tot3] = x % 10 ^ 48;
}
int main()
{
    
    ui n1, n2, N;
    register ui i, j, k;
    ui N_now = 0, tmp; 
    FILE *in = fopen("article.txt", "rb");
    n1 = fread(art + 1, 1, 7000000, in);
    // clock_t t = clock();
    art[n1 + 1] = 0;
    i = 1;
    while (art[i])
    {
        tmp = 0;
        while (ascii[art[i]])
        {
            if (!trie[tmp].nxt[alpha[art[i]]])
                trie[tmp].nxt[alpha[art[i]]] = ++tot;
            tmp = trie[tmp].nxt[alpha[art[i++]]];
        }
        ++trie[tmp].cnt;
        word[i] = tmp;
        while (art[i] && !ascii[art[i]])
            ++i;
    }
    fclose(in);
    // t = clock() - t;
    // printf("in time:%lf\n", ((float)t) / CLOCKS_PER_SEC);

    // t = clock();
    in = fopen("stopwords.txt", "rb");
    n2 = fread(sw + 1, 1, 7000000, in);
    sw[n1 + 1] = 0;
    i = 1;
    while (sw[i])
    {
        tmp = 0;
        while (ascii[sw[i]])
        {
            tmp = trie[tmp].nxt[alpha[sw[i]]];
            if (!tmp)
            {
                while (ascii[sw[i]])
                    ++i;
                break;
            }
            ++i;
        }
        trie[tmp].cnt = 0;
        while (sw[i] && !ascii[sw[i]])
            ++i;
    }
    fclose(in);
    // t = clock() - t;
    // printf("sw time:%lf\n", ((float)t) / CLOCKS_PER_SEC);

    // t = clock();
    i = 1;
    end['.'] = end['!'] = end['?'] = 1;
    ui sum = 0, cnt_max = 0;
    while (art[i])
    {
        while (art[i] == 32)
            ++i;
        if (!art[i])
            break;
        s[++tots].st = &art[i];
        while (!end[art[i]])
        {
            ++i;
            sum += trie[word[i]].cnt;
        }
        s[tots].ed = &art[i];
        bas[sum][++bas_cnt[sum]] = tots;
        if (cnt_max < sum)
            cnt_max = sum;
        sum = 0;
        ++i;
    }
    // t = clock() - t;
    // printf("sort time:%lf\n", ((float)t) / CLOCKS_PER_SEC);

    // t = clock();
    N = read();
    // N = 10000;
    FILE *out = fopen("results.txt", "w");
    ui num;
    uc *ch;
    for (i = cnt_max; i; --i)
    {
        for (j = 1; j <= bas_cnt[i]; ++j)
        {
            num = bas[i][j];
            print(i);
            buffer[++tot3] = 32;
            for (ch = s[num].st; ch != s[num].ed; ++ch)
                buffer[++tot3] = *ch;
            buffer[++tot3] = *ch;
            ++N_now;
            if (N_now == 5)
            {
                for (k = 1; k <= tot3; ++k)
                    putchar(buffer[k]);
                if (N < 5)
                    return 0;
            }
            buffer[++tot3] = '\n';
            if (N_now == N)
            {
                fwrite(buffer + 1, 1, tot3, out);
                fclose(out);
                // t = clock() - t;
                // printf("out time:%lf\n", ((float)t) / CLOCKS_PER_SEC);
                if (N_now >= 5)
                    return 0;
            }
        }
    }
    return 0;
}
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <stdio.h>

#define uc unsigned char
#define ui unsigned int
#define p ((1 << 19) - 1)

struct node1
{
    ui cnt, next;
    uc *st, *ed;
}ha[500000];
struct node2
{
    ui cnt;
    uc *st, *ed;
}ans[500000];
ui tot1 = 0, tot2 = 0, tot3 = 0, tot4 = 0;
uc art[10000010], sw[10000010], buffer[10000000];
ui link[p + 10] = {0};
struct node3
{
    ui num;
    struct node3 *next;
}bas[500000];
ui bas_has[500000] = {0};
struct node3 *bas_st[500000], *bas_ed[500000];

inline int scmp(uc *st1, uc *ed1, uc *st2, uc *ed2)
{
    if (ed1 - st1 != ed2 - st2)
        return 0;
    while (((*st1) | 32) == ((*st2) | 32) && ed1 - st1 && ed2 - st2)
        ++st1, ++st2;
    return ((*st1) | 32) == ((*st2) | 32) && ed1 == st1 && ed2 == st2;
}
void print(ui x)
{
    if (x > 9)
        print(x / 10);
    buffer[++tot3] = x % 10 ^ 48;
}
int main()
{
    FILE *in, *out;
    ui n1, n2, i, j, hv, flag = 0;
    uc *st, *ed;

    in = fopen("article.txt","rb");
    n1 = fread(art + 1, 1, 10000000, in);
    art[n1 + 1] = 0;
    i = 1;
    while (i <= n1)
    {
        while (i <= n1 && ((art[i] | 32) < 'a' || (art[i] | 32) > 'z'))
            ++i;
        if (i > n1)
            break;
        st = &art[i];
        hv = 0;
        while (i <= n1 && (art[i] | 32) <= 'z' && (art[i] | 32) >= 'a')
            hv = hv * 13131 + (art[i] | 32),
            ++i;
        hv &= p;
        ed = &art[i - 1];
        flag = 0;
        for (j = link[hv]; j; j = ha[j].next)
            if (scmp(ha[j].st, ha[j].ed, st, ed))
            {
                ++ha[j].cnt;
                flag = 1;
                break;
            }
        if (!flag)
        {
            ha[++tot1].cnt = 1;
            ha[tot1].next = link[hv];
            ha[tot1].st = st;
            ha[tot1].ed = ed;
            link[hv] = tot1;
        }
    }
    fclose(in);

    in = fopen("stopwords.txt","rb");
    n2 = fread(sw + 1, 1, 10000000, in);
    sw[n2 + 1] = 0;
    i = 1;
    while (i <= n2)
    {
        while (i <= n2 && (sw[i] < 'a' || sw[i] > 'z'))
            ++i;
        if (i > n2)
            break;
        st = &sw[i];
        hv = 0;
        while (i <= n2 && sw[i] >= 'a' && sw[i] <= 'z')
            hv = hv * 13131 + sw[i],
            ++i;
        hv &= p;
        ed = &sw[i - 1];
        for (j = link[hv]; j; j = ha[j].next)
        {
            if (scmp(ha[j].st, ha[j].ed, st, ed))
            {
                ha[j].cnt = 0;
                break;
            }
        }
    }
    fclose(in);

    i = 1;
    while (art[i] == ' ')
        ++i;
    st = &art[i];
    ui cnt = 0, max_cnt = 0;
    uc *stw, *edw;
    while (i <= n1)
    {
        flag = 0;
        while (i <= n1 && ((art[i] | 32) < 'a' || (art[i] | 32) > 'z'))
        {
            if (art[i] == '.' || art[i] == '?' || art[i] == '!')
            {
                flag = 1;
                ed = &art[i];
                ++i;
                break;
            }
            ++i;
        }
        if (flag)
        {
            ans[++tot2].cnt = cnt;
            ans[tot2].st = st;
            ans[tot2].ed = ed;
            if (!bas_has[cnt])
            {
                bas_has[cnt] = 1;
                bas[++tot4].num = tot2;
                bas[tot4].next = NULL;
                bas_ed[cnt] = bas_st[cnt] = &bas[tot4];
            }
            else
            {
                bas[++tot4].num = tot2;
                bas[tot4].next = NULL;
                bas_ed[cnt]->next = &bas[tot4];
                bas_ed[cnt] = bas_ed[cnt]->next; 
            }
            if (cnt > max_cnt)
                max_cnt = cnt;
            cnt = 0;
            if (i > n1)
                break;
            st = ed + 1;
            while (*st == ' ')
                ++st;
        }
        if (i > n1)
            break;
        stw = &art[i];
        hv = 0;
        while (i <= n1 && (art[i] | 32) >= 'a' && (art[i] | 32) <= 'z')
            hv = hv * 13131 + (art[i] | 32),
            ++i;
        hv &= p;
        edw = &art[i - 1];
        for (j = link[hv]; j; j = ha[j].next)
        {
            if (scmp(ha[j].st, ha[j].ed, stw, edw))
            {
                cnt += ha[j].cnt;
                break;
            }
        }
    }

    struct node3 *jj;
    ui N, N_now = 1, num;
    out = fopen("results.txt", "w");
    scanf("%d", &N);
    for (i = max_cnt; i && N_now <= N; --i)
    {
        if (!bas_has[i])
            continue;
        for (jj = bas_st[i]; jj != NULL && N_now <= N; jj = jj->next)
        {
            num = jj->num;
            print(i);
            buffer[++tot3] = 32;
            st = ans[num].st;
            ed = ans[num].ed;
            while (ed - st)
                buffer[++tot3] = *st,
                ++st;
            buffer[++tot3] = *ed;
            buffer[++tot3] = '\n';
            if (N_now == 5)
            {
                buffer[tot3 + 1] = 0;
                printf("%s", buffer + 1);
            }
            ++N_now;
        }
    }
    fwrite(buffer + 1, 1, tot3, out);
    fclose(out);
    return 0;
}
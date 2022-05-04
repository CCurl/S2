// S2.c - inspired by, and based on, STABLE from Sandor Schneider
// #define _CRT_SECURE_NO_WARNINGS    // For Visual Studio
// #include <windows.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define btw(a,b,c) ((b<=a) && (a<=c))
#define TOS st.i[s]
#define NOS st.i[s-1]
#define SZ 10000
union flin { float f[SZ/4]; int i[SZ/4]; char b[SZ]; }; static union flin st;
static char ex[80], *y; static int c, h, r, cb=SZ-3000, p, s, ro=64, rb=35, sb=3, t, u;
/* yex */ void yex() { y=ex; while (st.b[p]!='`') { *(y++)=st.b[p++]; } *y=0; ++p; }
/* <33 */ void X()   { if (u && (u!=10)) printf("-IR %d?", u); p=0; } void N() {}
/*  !  */ void f33() { st.i[TOS]=NOS; s-=2; }
/*  "  */ void f34() { while (st.b[p]!='"') { putc(st.b[p++], stdout); } ++p; }
/*  #  */ void f35() { t=TOS; st.i[++s]=t; }
/*  $  */ void f36() { t=TOS; TOS=NOS; NOS=t; }
/*  %  */ void f37() { t=NOS; st.i[++s]=t; }
/*  '  */ void f39() { st.i[++s]=st.b[p++]; }
/*  (  */ void f40() { if (st.i[s--]==0) { while (st.b[p++]!=')'); } }
/*  *  */ void f42() { NOS *= TOS; s--; }
/*  +  */ void f43() { NOS += TOS; s--; }
/*  ,  */ void f44() { putc(st.i[s--], stdout); }
/*  -  */ void f45() { NOS -= TOS; s--; }
/*  .  */ void f46() { printf("%d", st.i[s--]); }
/*  /  */ void f47() { NOS /= TOS; s--; }
/* 0-9 */ void n09() { st.i[++s]=(u-'0'); while (btw(st.b[p],'0','9')) { TOS=(TOS*10)+st.b[p++]-'0'; }
            if (st.b[p]=='e') { ++p; st.f[s]=(float)TOS; } }
/*  :  */ void f58() { u=st.b[p++]; if (btw(u,'A','Z')) { st.i[u]=p; while (st.b[p++]!=';'); if (h<p) h=p; } }
/*  ;  */ void f59() { p=st.i[r--]; if (r<rb) { r=rb; p=0; } }
/*  <  */ void f60() { t=TOS; u=NOS; s--; TOS=(u<t)?-1:0; if (st.b[p]=='=') { ++p; TOS=(u<=t)?-1:0; } }
/*  =  */ void f61() { NOS=(NOS==TOS)?-1:0; s--; }
/*  <  */ void f62() { t=TOS; u=NOS; s--; TOS=(u>t)?-1:0; if (st.b[p]=='=') { ++p; TOS=(u>=t)?-1:0; } }
/*  ?  */ void f63() { c=fgetc(stdin); st.i[++s]=(c!=EOF)?c:0; }
/*  @  */ void f64() { TOS=st.i[TOS]; }
/* A-Z */ void AZ()  { st.i[++r]=p; p=st.i[u]; }
/*  [  */ void f91() { st.i[++r]=p; st.i[++r]=st.i[s--]; st.i[++r]=st.i[s--]; }
/*  \  */ void f92() { --s; }
/*  ]  */ void f93() { ++st.i[r]; if (st.i[r] <= st.i[r-1]) { p=st.i[r-2]; } else { r-=3; } }
/*  ^  */ void f94() { p=st.i[r--]; }
/*  _  */ void f95() { TOS=-TOS; }
/*  `  */ void f96() { yex(); system(ex); }
/*  b  */ void f98() { u=st.b[p++]; if (u=='&') { NOS&=TOS; s--; }
            else if (u=='|') { NOS|=TOS; s--; }
            else if (u=='^') { NOS^=TOS; s--; }
            else if (u=='~') { TOS=~TOS; }
            else { putc(32, stdout); --p; } }
/*  c  */ void f99()  { u=st.b[p++]; if (u=='@') { TOS=st.b[TOS]; } else if (u=='!') { st.b[TOS]=NOS; s -= 2; } }
/*  d  */ void f100() { u=st.b[p++]; st.i[++s]=st.i[ro+u]; st.i[ro+u]--; }
/*  e  */ void f101() { st.i[++r]=p; p=st.i[s--]; }
/*  f  */ void f102() { u=st.b[p++]; if (u=='.') { printf("%f", st.f[s--]); }
            else if (u=='@') { st.f[s]=st.f[TOS]; }
            else if (u=='!') { st.f[TOS]=st.f[s-1]; s-=2; }
            else if (u=='+') { st.f[s-1]+=st.f[s]; s--; }
            else if (u=='-') { st.f[s-1]-=st.f[s]; s--; }
            else if (u=='*') { st.f[s-1]*=st.f[s]; s--; }
            else if (u=='/') { st.f[s-1]/=st.f[s]; s--; }
            else if (u=='<') { TOS=(st.f[s-1]<st.f[s]) ? -1 : 0; }
            else if (u=='>') { TOS=(st.f[s-1]>st.f[s]) ? -1 : 0; }
            else if (u=='O') { y=&st.b[NOS]; t=TOS; NOS=(int)fopen(y, (t)?"wb":"rb"); s--; }
            else if (u=='C') { if (TOS) { fclose((FILE*)TOS); } s--; }
            else if (u=='R') { s++; TOS=0; if (NOS) fread((void*)&TOS, 1, 1, (FILE*)NOS); }
            else if (u=='W') { fwrite((void*)&NOS, 1, 1, (FILE*)TOS); s-=2; } }
/*  i  */ void f105() { u=st.b[p++]; st.i[++s]=st.i[ro+u]; st.i[ro+u]++; }
/*  l  */ void f108() { u=st.b[p++]; if (u=='@') { TOS=*((int*)TOS); } /*else if (u=='!') { *((int *)TOS)=NOS; s-=2; }*/ }
/*  m  */ void f109() { u=st.b[p++]; if (u=='@') { TOS=*((char*)TOS); } /*else if (u=='!') { *((char*)TOS)=NOS; s-=2; }*/ }
/*  q  */ void f113() { for (int i=sb; i<=s; i++) { printf("%c%d", (i==sb)?0:32, st.i[i]); } }
/*  r  */ void f114() { u=st.b[p++]; st.i[++s]=st.i[ro+u]; }
/*  s  */ void f115() { u=st.b[p++]; st.i[ro+u]=st.i[s--]; }
/*  t  */ void f116() { st.i[++s]=1; } // { st.i[++s]=GetTickCount(); }
/*  x  */ void f120() { u=st.b[p++]; if (u=='I') { st.i[++s]=st.i[r]; }
            else if (u=='U') { --r; }
            else if (u=='W') { while (st.b[p++]!='}'); r--; }
            else if (u=='F') { while (st.b[p++]!=']'); r-=3; }
            else if (u=='%') { NOS %= TOS; s--; }
            else if (u=='Q') { exit(0); } }
/*  {  */ void f123() { st.i[++r]=p; if (TOS==0) { while (st.b[p]!='}') { ++p; } } }
/*  }  */ void f125() { if (TOS) { p=st.i[r]; } else { --r; --s; } }
/*  ~  */ void f126() { TOS = (TOS) ? 0 : -1; }
void (*q[127])()={ X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,N,f33,f34,f35,f36,f37,X,
f39,f40,N,f42,f43,f44,f45,f46,f47,n09,n09,n09,n09,n09,n09,n09,n09,n09,n09,f58,f59,f60,f61,f62,f63,f64,
AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,AZ,f91,f92,f93,f94,f95,f96,X,
f98,f99,f100,f101,f102,X,X,f105,X,X,f108,f109,X,X,X,f113,f114,f115,f116,X,X,X,f120,X,X,f123,X,f125,f126 };
void R(int x) { s=(s<sb)?(sb-1):s; r=rb; p=x; while (p) { u=st.b[p++]; q[u](); } }
void H(char *s) { FILE *fp=fopen("h.txt", "at"); if (fp) { fprintf(fp, "%s", s); fclose(fp); } }
void L() { y=&st.b[h]; printf("\ns2:("); f113(); printf(")>"); fgets(y, 128, stdin); H(y); R(h); }
void main(int argc, char *argv[]) {
    s=sb-1; h=cb; u=1000; for (int i=0; i<(SZ/4); i++) { st.i[i]=0; }
    for (int i = 1; i < argc; ++i) { y=argv[i]; t=atoi(y); 
        if ((t) || (y[0]=='0' && y[1]==0)) { st.i[ro+'0'+i]=t; }
        else { st.i[ro+'0'+i]=u; for (int j=0; y[j]; j++) { st.b[u++]=y[j]; } st.b[u++]=0; } }
    if ((argc>1) && (argv[1][0]!='-')) { FILE *fp=fopen(argv[1], "rb"); 
        if (fp) {while ((c=fgetc(fp))!=EOF) { if (btw(c,32,126)) st.b[h++]=c; } fclose(fp); R(cb); } else { printf("file?"); }
    } while (1) { L(); };
}
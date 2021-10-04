LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);
void print_string(float x, float y, char *text, float r, float g, float b);
void PlaceText(float x, float y, char* text, float r, float g, float b, float scalex, float scaley);


// declaration of needed functions

void circ(float x, float y, float r);
void rect(float lbx, float lby, float rtx, float rty);
void printgrid();
void drawballs(struct obj* Num, int N);
void userdialog();
void MatrixChange();
void Part_Param_Assign(struct obj* Num, int N);
void MolecDraw(struct obj* Num);
void plotting(struct vel* Maxwell);
void bouncing(struct obj* Num);
void DataCollect(struct obj* Num, struct vel* Maxwell);
void SavePrintData(struct vel* Maxwell);
void defspd(int* spd, int* T);
void header();
void KeysInstruct();
double cosine(float r1x, float r1y, float r2x, float r2y);
float avgspeed(struct obj* Num, int N);
float avgsqrspeed(struct obj* Num, int N);
int Maximum(int* a, int arsize);



// declaration of needed variables

int width = 128;
int lenght = 128;
int time = 0;
int turn = 0;
int tip = 0;
int timestop = 0;
int showgraph = 0;
int strip = 0;
float scale = -7.2;
float v1x = 0;
float v1y = 0;
float v2x = 0;
float v2y = 0;
float r1x = 0;
float r1y = 0;
float r2x = 0;
float r2y = 0;
float R = 0;
int T = 0;
int spd = 100;
int radconst = 0;
int N = 0;
char start_ans[15];
char grid[5];
int gr = 0;
int stat = 0;
char stat_ans[5];
char Y[5][6] = {"O,5%", "1,O%", "1,5%", "2,O%", "2,5%"};
char X[9][6] = {"300", "600", "900", "1200", "1500", "1800", "2100", "2400", "2700"};
FILE* fpx;
FILE* fpy;


struct obj
{
    float rx;
    float ry;
    float vx;
    float vy;
    float mass;
    float R;
    float r;
    float g;
    float b;
};


struct vel
{
    int n;
    float v;
};



void circ(float x, float y, float r)
{
            glBegin(GL_TRIANGLE_FAN);

            glVertex2f(x, y);

            for(int i = -1; i < 360; i++)
            glVertex2f(r * cos(i * M_PI/180) + x, r * sin(i * M_PI/180) + y);

            glEnd();
}


double cosine(float r1x, float r1y, float r2x, float r2y)
{
    return (r1x * r2x + r1y * r2y)/sqrt(r1x * r1x + r1y * r1y)/sqrt(r2x * r2x + r2y * r2y);
}


float avgspeed(struct obj* Num, int N)
{
    float v = 0;
    for(int i = 0; i < N; i++)
    {
        v +=  sqrt(Num[i].vx * Num[i].vx + Num[i].vy * Num[i].vy);
    }
    return v/N;
}


float avgsqrspeed(struct obj* Num, int N)
{
    float v = 0;
    for(int i = 0; i < N; i++)
    {
        v += Num[i].vx * Num[i].vx + Num[i].vy * Num[i].vy;
    }
    return sqrt(v/N);
}


void rect(float lbx, float lby, float rtx, float rty)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(lbx, lby);
    glVertex2f(lbx, rty);
    glVertex2f(rtx, lby);
    glVertex2f(rtx, rty);
    glVertex2f(lbx, rty);
    glVertex2f(rtx, lby);
    glEnd();
}


int Maximum(int* a, int arsize)
{
    int i = 0, j = 0;
    int temp = 0;

    for (i = 0; i < arsize; i++)
        for (j = 0; j < arsize; j++)
        {
            if (a[i] < a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;

            }
        }
    return a[arsize - 1];
}


void print_string(float x, float y, char *text, float r, float g, float b)
{
  static char buffer[99999];
  int num_quads;

  num_quads = stb_easy_font_print(x, y, text, NULL, buffer, sizeof(buffer));

  glColor3f(r,g,b);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 16, buffer);
  glDrawArrays(GL_QUADS, 0, num_quads*4);
  glDisableClientState(GL_VERTEX_ARRAY);
}


void printgrid()
{
    glLineWidth(0.01);

    glBegin(GL_LINES);


    for (int j = -width; j < width + 1; j++)
    {
        glVertex2f((float)j, -width);
        glVertex2f((float)j, width);

        glVertex2f(-width, (float)j);
        glVertex2f(width, (float)j);
    }

    glEnd();

    circ(0, 0, 0.03);
}


void drawballs(struct obj* Num, int N)
{
    int t = 0;
    for(t = 0; t < N; t++)
    {
        glColor3f(Num[t].r, 0, Num[t].b);
        circ(Num[t].rx, Num[t].ry, Num[t].R);
    }
}


void defspd(int* spd, int* T)
{
    if(*T > 500 && *T <= 1000)
    {
    *spd += 10;
    Y[0][0] = 'O';
    Y[0][1] = ',';
    Y[0][2] = '4';
    Y[0][3] = '%';

    Y[1][0] = 'O';
    Y[1][1] = ',';
    Y[1][2] = '8';
    Y[1][3] = '%';

    Y[2][0] = '1';
    Y[2][1] = ',';
    Y[2][2] = '2';
    Y[2][3] = '%';

    Y[3][0] = '1';
    Y[3][1] = ',';
    Y[3][2] = '6';
    Y[3][3] = '%';

    Y[4][0] = '2';
    Y[4][1] = ',';
    Y[4][2] = 'O';
    Y[4][3] = '%';
    }
    if(*T > 1000 && *T <= 1500)
    {
    *spd += 35;
    Y[0][0] = 'O';
    Y[0][1] = ',';
    Y[0][2] = '3';
    Y[0][3] = '%';

    Y[1][0] = 'O';
    Y[1][1] = ',';
    Y[1][2] = '6';
    Y[1][3] = '%';

    Y[2][0] = 'O';
    Y[2][1] = ',';
    Y[2][2] = '9';
    Y[2][3] = '%';

    Y[3][0] = '1';
    Y[3][1] = ',';
    Y[3][2] = '2';
    Y[3][3] = '%';

    Y[4][0] = '1';
    Y[4][1] = ',';
    Y[4][2] = '5';
    Y[4][3] = '%';
    }


    if(*T > 1500 && *T <= 2000)
    {
    *spd += 50;
    Y[0][0] = 'O';
    Y[0][1] = ',';
    Y[0][2] = '2';
    Y[0][3] = '5';
    Y[0][4] = '%';

    Y[1][0] = 'O';
    Y[1][1] = ',';
    Y[1][2] = '5';
    Y[1][3] = 'O';
    Y[1][4] = '%';

    Y[2][0] = 'O';
    Y[2][1] = ',';
    Y[2][2] = '7';
    Y[2][3] = '5';
    Y[2][4] = '%';

    Y[3][0] = '1';
    Y[3][1] = ',';
    Y[3][2] = 'O';
    Y[3][3] = 'O';
    Y[3][4] = '%';

    Y[4][0] = '1';
    Y[4][1] = ',';
    Y[4][2] = '2';
    Y[4][3] = '5';
    Y[4][4] = '%';
    }
    if(*T > 2000)
    {
    *spd += 70;
    Y[0][0] = 'O';
    Y[0][1] = ',';
    Y[0][2] = '1';
    Y[0][3] = '5';
    Y[0][4] = '%';

    Y[1][0] = 'O';
    Y[1][1] = ',';
    Y[1][2] = '3';
    Y[1][3] = 'O';
    Y[1][4] = '%';

    Y[2][0] = 'O';
    Y[2][1] = ',';
    Y[2][2] = '4';
    Y[2][3] = '5';
    Y[2][4] = '%';

    Y[3][0] = 'O';
    Y[3][1] = ',';
    Y[3][2] = '6';
    Y[3][3] = 'O';
    Y[3][4] = '%';

    Y[4][0] = 'O';
    Y[4][1] = ',';
    Y[4][2] = '7';
    Y[4][3] = '5';
    Y[4][4] = '%';
    }
}


void userdialog()
{
    printf("Start or Quit?\n");
    scanf("%s", start_ans);

    if (start_ans[0] == 'Q' || start_ans[0] == 'E')
        exit(1);

    printf("\n");

    printf("Test statistics?\n");
    scanf("%s", stat_ans);
    if(stat_ans[0] == 'Y' || stat_ans[0] == 'y')
        stat = 1;

    printf("\n");

    printf("Enter the number of particles: ");
    scanf("%d", &N);

    printf("\n");

    printf("Enter the radius constant: ");
    scanf("%d", &radconst);

    printf("\n");

    printf("Enter the temperature in Kelvins: ");
    scanf("%d", &T);

    printf("\n");

    if(N <= 1000)
    {
        printf("Do you need a grid?\n");
        scanf("%s", grid);

        printf("\n");
        if (grid[0] == 'Y' || grid[0] == 'y')
            gr = 1;
    }
}


void Part_Param_Assign(struct obj* Num, int N)
{
    int k = 0;
    for (k = 0; k < N; k++)         // assigning every particle its parameters
    {
            Num[k].rx = ((float)(rand() % (200 * width)) - 100 * width)/100;
            Num[k].ry = ((float)(rand() % (200 * width)) - 100 * width)/100;
            Num[k].vx = (float)(rand() % 10000 - 5000) * sqrt(T)*2;
            Num[k].vy = (float)(rand() % 10000 - 5000) * sqrt(T)*2;
            Num[k].mass = 1;
            Num[k].r = 0.2;
            Num[k].g = 0.3;
            Num[k].b = 0.4;
    }


    R = 0.15 * radconst * exp(0.333 * log(Num[0].mass));

    for(k = 0; k < N; k++)
        Num[k].R = R;
}


void MolecDraw(struct obj* Num)
{

    glColor3f(0, 1, 0);
    glTranslatef(0, -15, 0);

    if (gr)                           // drawing grid
    printgrid();

    glLineWidth(1);

    if(N <= 1000)
    drawballs(Num, N);




    glColor3f(0, 0, 0);                   // walls drawing
    glBegin(GL_LINES);

    glVertex2f(width, -width);
    glVertex2f(width, width);


    glVertex2f(width, -width);
    glVertex2f(-width, -width);


    glVertex2f(-width, -width);
    glVertex2f(-width, width);


    glVertex2f(-width, width);
    glVertex2f(width, width);


    glEnd();
}


void plotting(struct vel* Maxwell)
{
    int t = 0;
    glColor3f(1, 1, 1);
    rect(-3*width/2 - 34, -width - 10, 3*width/2 + 15, width);

    glColor3f(0, 0, 0);

    glBegin(GL_LINES);                           // drawing axes

    glVertex2f(-3*width/2 - 10, -width + 5);
    glVertex2f(3*width/2 + 10, -width + 5);

    glVertex2f(-3*width/2 - 10, -width + 5);
    glVertex2f(-3*width/2 - 10, width - 5);

    glEnd();



    glBegin(GL_TRIANGLES);                        // axes arrows drawing

    glVertex2f(3*width/2 + 10, -width + 5);
    glVertex2f(3*width/2, -width + 1);
    glVertex2f(3*width/2, -width + 5);


    glVertex2f(3*width/2 + 10, -width + 5);
    glVertex2f(3*width/2, -width + 9);
    glVertex2f(3*width/2, -width + 5);


    glVertex2f(-3*width/2 - 10, width - 5);
    glVertex2f(-3*width/2 - 6, width - 15);
    glVertex2f(-3*width/2 - 10, width - 15);


    glVertex2f(-3*width/2 - 10, width - 5);
    glVertex2f(-3*width/2 - 14, width - 15);
    glVertex2f(-3*width/2 - 10, width - 15);


    glEnd();



    glLineWidth(0.02);
    glBegin(GL_LINES);

    for(t = -width + 44; t < width - 4; t += 39)
    {                                                      // horizontal grid lines
        glVertex2f(-3*width/2 - 10, t);
        glVertex2f(3*width/2 + 10, t);
    }


    for(t = -3*width/2 + 29; t <= 3*width/2 + 10; t += 39)
    {
        glVertex2f(t, -width + 5);                         // vertical grid lines
        glVertex2f(t,  width - 5);
    }

    glEnd();



    glLineWidth(3);
    glColor3f(0, 0, 0);                          // graph box edge drawing
    glBegin(GL_LINES);


    glVertex2f(-3*width/2 - 34, -width - 10);
    glVertex2f(-3*width/2 - 34, width);

    glVertex2f(-3*width/2 - 34, width);
    glVertex2f(3*width/2 + 15, width);

    glVertex2f(3*width/2 + 15, width);
    glVertex2f(3*width/2 + 15, -width - 10);

    glVertex2f(3*width/2 + 15, -width - 10);
    glVertex2f(-3*width/2 - 34, -width - 10);

    glEnd();



    PlaceText(-3*width/2 - 16, -width + 5, "O", 0, 0, 0, 0.75, 0.75);

    for(int i = 0; i < 5; i++)
    PlaceText(-3*width/2 - 32, -width + 47 + 39*i, Y[i], 0, 0, 0, 0.75, 0.75);

    glLineWidth(0.1);
    glBegin(GL_LINE_STRIP);

        glVertex2f(-3*width/2 - 31, -width + 245);
        glVertex2f(-3*width/2 - 29, -width + 248);

        glVertex2f(-3*width/2 - 27, -width + 245);
        glVertex2f(-3*width/2 - 31, -width + 245);

    glEnd();

    glBegin(GL_LINES);
        glVertex2f(-3*width/2 - 31, -width + 243);
        glVertex2f(-3*width/2 - 20, -width + 243);
    glEnd();

    PlaceText(-3*width/2 - 25, -width + 250, "N", 0, 0, 0, 0.75, 0.75);
    PlaceText(-3*width/2 - 27, -width + 240, "N", 0, 0, 0, 0.75, 0.75);
    PlaceText(-3*width/2 - 19, -width + 245, "%", 0, 0, 0, 0.75, 0.75);




    for(int i = 0; i < 9; i++)
    PlaceText(-3*width/2 + 22 + 39*i, -width + 2, X[i], 0, 0, 0, 0.75, 0.75);

    PlaceText(-3*width/2 + 370, -width + 2, "v, m/c", 0, 0, 0, 0.8, 0.8);



    glColor3f(1, 0, 0);
    glPointSize(4);
    glLineWidth(3);
    if(strip == 1)
    glBegin(GL_LINE_STRIP);
    else
    glBegin(GL_POINTS);


    for (t = 0; t < spd; t++)              // drawing graph dots
    {

        if(-width + 5 + (double)Maxwell[t].n / (double)(N * time + 0.1) * 2.6 * sqrt(T) * width < width)
        glVertex2f(-3*width/2 - 10 + Maxwell[t].v * (3*width + 8) / Maxwell[spd - 1].v, -width + 5 + (double)Maxwell[t].n / (double)(N * time + 0.1) * 2.6 * sqrt(T) * width);
    }

    glEnd();
}


void bouncing(struct obj* Num)
{
    int t = 0;
    int k = 0;
    for(t = 0; t < N; t++)
    {
        Num[t].rx += dt * Num[t].vx;
        Num[t].ry += dt * Num[t].vy;
    }

    for (t = 0; t < N; t++)
    {
        if(Num[t].rx >= width - 0.05 - R)
        {
            Num[t].vx *= -1.0;
            Num[t].rx = width - 0.05 - R;
        }

        if(Num[t].ry >= width - 0.05 - R)
        {
            Num[t].vy *= -1.0;
            Num[t].ry = width - 0.05 - R;
        }

        if(Num[t].rx <= -width + 0.05 + R)
        {
            Num[t].vx *= -1.0;
            Num[t].rx = -width + 0.05 + R;
        }

        if(Num[t].ry <= -width + 0.05 + R)
        {
            Num[t].vy *= -1.0;
            Num[t].ry = -width + 0.05 + R;
        }
    }



for (t = 0; t < N; t++)
    for(k = t + 1; k < N; k++)
    {
        if ((Num[t].rx - Num[k].rx) * (Num[t].rx - Num[k].rx) + (Num[t].ry - Num[k].ry) * (Num[t].ry - Num[k].ry) <= 4*R*R)
        {
            v1x = Num[t].vx;
            v1y = Num[t].vy;

            v2x = Num[k].vx;
            v2y = Num[k].vy;

            r1x = Num[t].rx;
            r1y = Num[t].ry;

            r2x = Num[k].rx;
            r2y = Num[k].ry;



            Num[t].vx = v1x - ((v1x - v2x)*(r1x - r2x) + (v1y - v2y)*(r1y - r2y)) / ((r1x - r2x) * (r1x - r2x) + (r1y - r2y) * (r1y - r2y)) * (r1x - r2x);
            Num[t].vy = v1y - ((v1x - v2x)*(r1x - r2x) + (v1y - v2y)*(r1y - r2y)) / ((r1x - r2x) * (r1x - r2x) + (r1y - r2y) * (r1y - r2y)) * (r1y - r2y);

            Num[k].vx = v2x - ((v2x - v1x)*(r2x - r1x) + (v2y - v1y)*(r2y - r1y)) / ((r1x - r2x) * (r1x - r2x) + (r1y - r2y) * (r1y - r2y)) * (r2x - r1x);
            Num[k].vy = v2y - ((v2x - v1x)*(r2x - r1x) + (v2y - v1y)*(r2y - r1y)) / ((r1x - r2x) * (r1x - r2x) + (r1y - r2y) * (r1y - r2y)) * (r2y - r1y);


            Num[t].rx += (Num[t].rx - Num[k].rx)*0.02;
            Num[t].ry += (Num[t].ry - Num[k].ry)*0.02;
            Num[k].rx += (Num[k].rx - Num[t].rx)*0.02;
            Num[k].ry += (Num[k].ry - Num[t].ry)*0.02;



        }
    }
}


void MatrixChange()
{
    if (scale >= 2)
        scale = -6;

        glScalef(exp(scale * log(2)), exp(scale * log(2)), 1);

        glTranslatef((float)turn/20, (float)tip/20, 0);
}


void DataCollect(struct obj* Num, struct vel* Maxwell)
{
    int t = 0;
    int k = 0;
    for(k = 0; k < spd; k++)
    {
        for(t = 0; t < N; t++)
        {
            if(sqrt(Num[t].vx * Num[t].vx + Num[t].vy * Num[t].vy)/200.0 > 2.0*dv*k - dv && sqrt(Num[t].vx * Num[t].vx + Num[t].vy * Num[t].vy)/200.0 < 2.0*dv*k + dv)
            Maxwell[k].n++;
        }
    }
}


void header()
{
    glColor3f(0, 0, 1);
    rect(-1, 0.9, 1, 1);

    glScalef(0.01, -0.01, 1);
    print_string(-55, -99, "Maxwell's Distribution", 0, 0, 0);
    glScalef(100, -100, 1);
}


void SavePrintData(struct vel* Maxwell)
{
    int k = 0;
    fpx = fopen("datax.txt", "w");       // saving x-data
        for(k = 0; k < spd; k++)
        {
            fprintf(fpx, "%lg\n", Maxwell[k].v);
        }

    fclose(fpx);


    fpy = fopen("datay.txt", "w");       // saving y-data
        for(k = 0; k < spd; k++)
        {
            fprintf(fpy, "%lg\n", 100.0*(double)Maxwell[k].n/(double)(N * time));
        }

    fclose(fpy);
}


void PlaceText(float x, float y, char* text, float r, float g, float b, float scalex, float scaley)
{
    glTranslatef(x, y, 0);
    glScalef(scalex, -scaley, 1);
    print_string(0, 0, text, r, g, b);
    glScalef(1/scalex, -1/scaley, 1);
    glTranslatef(-x, -y, 0);
}


void KeysInstruct()
{
    if(!showgraph)
    {
        glColor3f(1, 0, 0);

        rect(-1, 0.8, -0.88, 0.9);
        rect(-0.82, 0.81, -0.1, 0.9);

        rect(0.02, 0.8, 0.28, 0.9);
        rect(0.37, 0.81, 0.9, 0.9);


        PlaceText(-0.96, 0.88, "g   switch graph mode    space   stop the time", 0, 0, 0, 0.007, 0.007);

        glColor3f(0, 0, 0);
        glLineWidth(0.5);

        glBegin(GL_LINES);
        glVertex2f(-1, 0.9);
        glVertex2f(1, 0.9);

        glVertex2f(-1, 0.8);
        glVertex2f(-0.88, 0.8);

        glVertex2f(-0.88, 0.8);
        glVertex2f(-0.88, 0.9);


        glVertex2f(-0.82, 0.81);
        glVertex2f(-0.1, 0.81);

        glVertex2f(-0.82, 0.81);
        glVertex2f(-0.82, 0.9);

        glVertex2f(-0.1, 0.81);
        glVertex2f(-0.1, 0.9);


        glVertex2f(0.02, 0.8);
        glVertex2f(0.02, 0.9);

        glVertex2f(0.02, 0.8);
        glVertex2f(0.28, 0.8);

        glVertex2f(0.28, 0.8);
        glVertex2f(0.28, 0.9);


        glVertex2f(0.37, 0.81);
        glVertex2f(0.37, 0.9);

        glVertex2f(0.37, 0.81);
        glVertex2f(0.9, 0.81);

        glVertex2f(0.9, 0.81);
        glVertex2f(0.9, 0.9);
        glEnd();

    }



    if(showgraph)
    {
        glColor3f(1, 0, 0);

        rect(-1, 0.8, -0.88, 0.9);
        rect(-0.82, 0.81, -0.1, 0.9);

        rect(0.18, 0.8, 0.3, 0.9);
        rect(0.37, 0.81, 0.81, 0.9);


        PlaceText(-0.96, 0.88, "g   switch graph mode        c   strip mode", 0, 0, 0, 0.007, 0.007);

        glColor3f(0, 0, 0);
        glLineWidth(0.5);

        glBegin(GL_LINES);
        glVertex2f(-1, 0.9);
        glVertex2f(1, 0.9);

        glVertex2f(-1, 0.8);
        glVertex2f(-0.88, 0.8);

        glVertex2f(-0.88, 0.8);
        glVertex2f(-0.88, 0.9);


        glVertex2f(-0.82, 0.81);
        glVertex2f(-0.1, 0.81);

        glVertex2f(-0.82, 0.81);
        glVertex2f(-0.82, 0.9);

        glVertex2f(-0.1, 0.81);
        glVertex2f(-0.1, 0.9);


        glVertex2f(0.18, 0.8);
        glVertex2f(0.18, 0.9);

        glVertex2f(0.18, 0.8);
        glVertex2f(0.3, 0.8);

        glVertex2f(0.3, 0.8);
        glVertex2f(0.3, 0.9);


        glVertex2f(0.37, 0.81);
        glVertex2f(0.37, 0.9);

        glVertex2f(0.37, 0.81);
        glVertex2f(0.81, 0.81);

        glVertex2f(0.81, 0.81);
        glVertex2f(0.81, 0.9);
        glEnd();

    }

}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_MOUSEWHEEL:                 // mousewheel - change scale
            if ((short)HIWORD(wParam) < 0)
            {
                scale -= 0.1;
            }
            else
            {
                scale += 0.1;
            }
        break;



        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;

                case VK_LEFT:
                    turn += 20;
                break;

                case VK_RIGHT:
                    turn -= 20;
                break;

                case VK_UP:
                    tip -= 20;
                break;

                case VK_DOWN:
                    tip += 20;
                break;

                case VK_TAB:              // tab - increase scale
                    scale++;
                break;

                case 0x20:                // space - timestop
                if (timestop == 0)
                {
                    timestop = 1;
                    break;
                }
                if (timestop == 1)
                {
                    timestop = 0;
                    break;
                }


                case 0x41:                // a - left
                    turn += 20;
                break;

                case 0x44:
                    turn -= 20;           // d - right
                break;

                case 0x57:                // w - up
                    tip -= 20;
                break;

                case 0x53:                // s - down
                    tip += 20;
                break;

                case 0x47:
                    if(showgraph == 0)    // g - show graph
                    {
                        showgraph = 1;
                        tip = 0;
                        turn = 20;
                        scale = -7.9;
                        break;
                    }

                    if(showgraph == 1)
                    {
                        showgraph = 0;
                        scale = -7.2;
                        tip = 0;
                        turn = 0;
                        break;
                    }
                case 0x43:                 // c - change strip mode
                    if(strip == 0)
                    {
                        strip = 1;
                        break;
                    }

                    if(strip == 1)
                    {
                        strip = 0;
                        break;
                    }


            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}


void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    *hDC = GetDC(hwnd);

    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}


void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

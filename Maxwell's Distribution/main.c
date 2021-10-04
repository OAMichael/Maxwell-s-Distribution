#define EnergyLoss 1
#define dt 0.00001
#define dv 15.0

#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stb_easy_font.h>
#include <Maxwell.h>


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)

{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;



    // dialog with user
    userdialog();


    system("cls");


    defspd(&spd, &T);                  // assigning speed value


    struct vel Maxwell[spd];           // defining Maxwell's Distribution array
    int testarray[spd];

    int k = 0;
    int t = 0;
    int Maxelement = 0;



    for(k = 0; k < spd; k++)           // filling it with velocities
    {
        Maxwell[k].v = 2.0*dv*k;
        Maxwell[k].n = 1;
    }

    struct obj Num[N];                 // defining particle array




    // creating OpenGL window

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "Maxwell's Distribution",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          768,
                          800,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    EnableOpenGL(hwnd, &hDC, &hRC);


    Part_Param_Assign(Num, N);



    while (!bQuit)          // main loop
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {

            glClearColor(0.0f, 0.8f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();

            MatrixChange();

            if (!showgraph)
            MolecDraw(Num);


            if(!timestop)
            {
                for(t = 0; t < spd; t++)
                        testarray[t] = Maxwell[t].n;

                    Maxelement = Maximum(testarray, spd);
            }


            if (showgraph)                              // graph drawing
            plotting(Maxwell);


            if(!timestop)                               // wall and each other bouncing
            bouncing(Num);


            glPopMatrix();


            header();
            KeysInstruct();

            SwapBuffers(hDC);


            if(!timestop)                                // collecting the data
            DataCollect(Num, Maxwell);


            if(time > 200 && stat == 1)
                break;


            printf("Average speed = %4.1f; root mean speed = %4.1f; time = %d; scale = %lg; max%% = %lg%%    \r", 
                    avgspeed(Num, N)/200.0, avgsqrspeed(Num, N)/200.0, time,   scale, 100*(double)Maxelement/((double)N*(double)time + 1.0));

            if(timestop != 1)
            time++;
            Sleep (0.1);
        }
    }

    DisableOpenGL(hwnd, hDC, hRC);

    DestroyWindow(hwnd);

    if(stat)
    SavePrintData(Maxwell);

    return msg.wParam;
}

#include "stdafx.h"
#include<stdio.h>
#include<GL/glut.h>

void trafikisaretleri();
void otobus();
void otobus2();
void otobus3();
void yol();
void yardimekrani();
void kontrol();
void mouse();
void araba1();
void araba2();
void ciz();
void goruntu();
void goruntu1();
void ekran();
void yaziTipiAyarla();
void guncelleme();

GLint a = 300, b = -300, flag = 0, trafik_duzenleyici = 1, kontrolanahtariL, kontrolanahtariR;
GLfloat kirmizi = 0, mavi = 1, yesil = .5;
GLfloat p = 0, q = 0, r = 0;
void* yaziTipiS;
void yaziTipiAyarla(void* yazitipi)
{
	yaziTipiS = yazitipi;
}

void yaz(float x, float y, float z, char* string)
{
	char* c;
	//Bitmap metinleri g�r�nt�leme,konumland�rma
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutBitmapCharacter(yaziTipiS, *c);
	}
}
void ekran(void)
{
	yaziTipiAyarla(GLUT_BITMAP_TIMES_ROMAN_24);
	glClearColor(0.8, 0.8, 0.7, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	yaz(450.0, 700.0, 0.0, "BURSA ULUDAG UNIVERSITESI");
	glColor3f(0, 0, 0);
	yaz(465, 650, 0.0, "BILGISAYAR MUHENDISLIGI");
	glColor3f(0, 0, 0);
	yaz(450, 600, 0.0, "BILGISAYAR GRAFIKLER� DERSI");
	glColor3f(0, 0, 0);
	yaz(535, 550, 0.0, " PROJE ODEVI");
	glColor3f(0, 0, 0);
	yaz(510, 400, 0.0, " TRAFIK SINYALLERI");
	yaz(450, 100, 0.0, "ENTER TUSUNA BASARAK BASLAYIN");
	glFlush();
}
void yardimekrani()
{
	yaziTipiAyarla(GLUT_BITMAP_TIMES_ROMAN_24);
	glClearColor(0.8, 0.8, 0.7, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 0);
	yaz(150.0, 640.0, 0.0, "KIRMIZI ISIK                                                                                            SOL TUSA TIKLAYIN");
	glColor3f(0, 0, 0);
	yaz(150.0, 570.0, 0.0, "SARI ISIK                                                                                                   SAG TUSA BASILI TUTUN");
	glColor3f(0, 0, 0);
	yaz(150.0, 500.0, 0.0, "YESIL ISIK                                                                                                 SAG TUSA BASMAYI BIRAKIN");
	glColor3f(0, 0, 0);
	yaz(150.0, 290.0, 0.0, "ARACLARIN HIZINI ARTTIRMA                                                          S TUSUNA BASIN");
	glColor3f(0, 0, 0);
	yaz(150.0, 430.0, 0.0, "ARACLARIN SOLDAN GECISINI SAGLAMAK                                  L TUSUNA BASIN");
	glColor3f(0, 0, 0);
	yaz(150.0, 360.0, 0.0, "ARACLARIN SAGDAN GECISINI SAGLAMAK                                  R TUSUNA BASIN");

	glColor3f(0, 0, 0);
	yaz(150.0, 220.0, 0.0, "YARDIM                                                                                                     H TUSUNA BASIN");
	glFlush();
}
void kontrol()
//ara�lar�n sa�dan m� soldan m� gidece�ini belirleme
{
	if (kontrolanahtariL != 'l' || kontrolanahtariR != 'r')
	{
		if (kontrolanahtariL == 'l')
			a = a + 6;
		if (kontrolanahtariR == 'r')
			b = b - 6;
	}
}
void klavye(unsigned char anahtar, int x, int y)
{
	switch (anahtar)
	{
	case 13:
		if (flag == 1)
		{
			flag = 2;
			goruntu();
		}
		if (flag == 0) //enter asc�� kodu
		{
			flag = 1; goruntu();
		}
		break;
	case 'l':kontrolanahtariL = anahtar;
		p = 0; q = 0; r = 1;
		break;
	case 'r':kontrolanahtariR = anahtar;
		p = 0; q = 0; r = 1;
		break;
	case 's':goruntu();
		break;
	case 'h':flag = 1; goruntu();
		break;
	default:break;
	}
}
void mouse(int buton, int durum, int x, int y)
{
	if (buton == GLUT_LEFT_BUTTON && durum == GLUT_DOWN)
	{
		trafik_duzenleyici = 0;
		p = 1;
		q = 0;
		r = 0;
	}
	if (buton == GLUT_RIGHT_BUTTON && durum == GLUT_DOWN)
	{
		trafik_duzenleyici = 0;
		p = 0;
		q = 1;
		r = 0;
	}
	if (buton == GLUT_RIGHT_BUTTON && durum == GLUT_UP)
	{
		trafik_duzenleyici = 1;
		p = 0;
		q = 0;
		r = 1;
	}
	//�ekli yeni koordinatlara y�kledik ve opengle hadi �iz diyoruz.
	glutPostRedisplay();
}
void goruntu(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (flag == 0)
		ekran();
	if (flag == 1)
		yardimekrani();
	if (flag == 2)
		goruntu1();
	//arka plandaki de�i�iklikleri �n plana yans�tma
	glutSwapBuffers();
}
void guncelleme(int value)
{
	a = a - 6;
	b = b + 6;
	kontrol();

	if (mavi != 0 && yesil != 0)
	{
		mavi -= .006; yesil -= .004;
	}
	glutPostRedisplay();
}
void goruntu1(void)
{
	if (trafik_duzenleyici)
		//animasyon s�ras� olu�turma
		glutTimerFunc(50, guncelleme, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(kirmizi, yesil, mavi, 0); //g�ky�z� renk	
	yol();
	otobus();
	otobus2();
	otobus3();
	trafikisaretleri();
	araba1();
	araba2();
	glFlush();
}
void yol()
{
	glPushMatrix(); // Anl�k olarak haf�zada haz�r bekleyen d�n���m� y���na koyar

	glScaled(40.0, 40.0, 0.0); //�l�ekleme yap�l�r
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);
	//yol
	glVertex2f(0, 5);
	glVertex2f(40, 5);
	glVertex2f(40, 10);
	glVertex2f(0, 10);
	glEnd();
	///alt k�s�m
	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.1, 0.1);
	glVertex2f(0, 5);
	glVertex2f(40, 5);
	glVertex2f(40, 4);
	glVertex2f(0, 4);
	glEnd();
	//yol2
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(27, 8);
	glVertex2f(20, 10);
	glVertex2f(20, 28);
	glVertex2f(18, 32);

	glColor3f(1.0, 1.0, 1.0);
	glLineStipple(3, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2f(0, 7.7);
	glVertex2f(38, 7.7)
		glEnd();
	glPopMatrix();  //y���nda en �stte olan matrisi alarak haf�zaya y�kler.
}
void trafikisaretleri()
{
	glPushMatrix();
	glScaled(45.0, 45.0, 20.0);
	//en alt k�s�m
	glColor3f(0.0, 0.1, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(15, 7);
	glVertex2f(15, 8);
	glVertex2f(18, 8);
	glVertex2f(18, 7);
	glEnd();
	//alt k�s�mla �st k�sm� birle�tiren yer
	glBegin(GL_POLYGON);
	glVertex2f(16, 7);
	glVertex2f(17, 8);
	glVertex2f(17, 15);
	glVertex2f(16, 15);
	glEnd();
	//�st k�s�m
	glBegin(GL_POLYGON);
	glVertex2f(15.5, 15);
	glVertex2f(17.5, 15);
	glVertex2f(17.5, 10);
	glVertex2f(15.5, 10);
	glEnd();
	//k�rm�z�
	glColor3f(p, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(16, 14.5);
	glVertex2f(17, 14.5);
	glVertex2f(17, 14);
	glVertex2f(16, 14);
	glEnd();
	//sar�
	glColor3f(q, q, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(16, 13.5);
	glVertex2f(17, 13.5);
	glVertex2f(17, 13);
	glVertex2f(16, 13);
	glEnd();
	//ye�il
	glColor3f(0.0, r, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(16, 12.5);
	glVertex2f(17, 12.5);
	glVertex2f(17, 12);
	glVertex2f(16, 12);
	glEnd();
	glPopMatrix();
}
void otobus()
{
	glPushMatrix();
	glTranslated(a, 50.0, 0.0); //Koordinatlar� a, 50.0, 0.0 ile belirtilen noktaya koordinat sistemini �teler.
	glScaled(40.0, 40.0, 0.0);
	glColor3f(0, 0, 1);
	//otobus d���
	glBegin(GL_POLYGON);
	glVertex2f(25, 8);
	glVertex2f(25, 9.5);
	glVertex2f(26, 11);
	glVertex2f(32, 11);
	glVertex2f(32, 8);
	glEnd();
	//pencere �er�evesi
	glColor3f(0, 0.1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(26.1, 9.5);
	glVertex2f(26.1, 10.5);
	glVertex2f(31.8, 10.5);
	glVertex2f(31.8, 9.5);
	glEnd();
	//kap�
	glColor3f(0, 0.8, 1);
	glBegin(GL_POLYGON);
	glVertex2f(26.2, 9);
	glVertex2f(26.2, 10.4);
	glVertex2f(27.7, 10.4);
	glVertex2f(27.7, 9);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(27, 8.4);
	glVertex2f(27, 10.4);
	glVertex2f(27.7, 10.4);
	glVertex2f(27.7, 8.4);
	glEnd();
	//k���k pencere
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(27.8, 9.6);
	glVertex2f(27.8, 10.4);
	glVertex2f(29, 10.4);
	glVertex2f(29, 9.6);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(29.1, 9.6);
	glVertex2f(29.1, 10.4);
	glVertex2f(30.2, 10.4);
	glVertex2f(30.2, 9.6);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(30.3, 9.6);
	glVertex2f(30.3, 10.4);
	glVertex2f(31.7, 10.4);
	glVertex2f(31.7, 9.6);
	glEnd();

	//s�r�c� penceresi
	glColor3f(0, 0.8, 1);
	glBegin(GL_POLYGON);
	glVertex2f(25, 9.5);
	glVertex2f(26, 11);
	glVertex2f(26, 9.5);
	glEnd();
	glPopMatrix();
	//tekerlekler
	glPushMatrix();//�n tekerlek
	glTranslated(a + 970, 320, 0.0);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();
	glPopMatrix();

	glPushMatrix();//arka tekerlek
	glTranslated(a + 1140, 320, 0.0);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();
	glPopMatrix();
}
void otobus2()
{
	glPushMatrix();
	glTranslated(a + 1500, 50.0, 0.0);
	glScaled(40.0, 40.0, 0.0);
	glColor3f(0.9, 0.8, 0.3);
	//otobus d���
	glBegin(GL_POLYGON);
	glVertex2f(25, 8);
	glVertex2f(25, 9.5);
	glVertex2f(26, 11);
	glVertex2f(32, 11);
	glVertex2f(32, 8);
	glEnd();
	//pencere �er�evesi
	glColor3f(0.9, 0.8, 0);
	glBegin(GL_POLYGON);
	glVertex2f(26.1, 9.5);
	glVertex2f(26.1, 10.5);
	glVertex2f(31.8, 10.5);
	glVertex2f(31.8, 9.5);
	glEnd();
	//kap�
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(26.2, 9);
	glVertex2f(26.2, 10.4);
	glVertex2f(27.7, 10.4);
	glVertex2f(27.7, 9);
	glEnd();

	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(27, 8.4);
	glVertex2f(27, 10.4);
	glVertex2f(27.7, 10.4);
	glVertex2f(27.7, 8.4);
	glEnd();
	//k���k pencere
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(27.8, 9.6);
	glVertex2f(27.8, 10.4);
	glVertex2f(29, 10.4);
	glVertex2f(29, 9.6);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(29.1, 9.6);
	glVertex2f(29.1, 10.4);
	glVertex2f(30.2, 10.4);
	glVertex2f(30.2, 9.6);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(30.3, 9.6);
	glVertex2f(30.3, 10.4);
	glVertex2f(31.7, 10.4);
	glVertex2f(31.7, 9.6);
	glEnd();

	//s�r�c� penceresi
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(25, 9.5);
	glVertex2f(26, 11);
	glVertex2f(26, 9.5);
	glEnd();
	glPopMatrix();
	//tekerlekler
	glPushMatrix();//�n tekerlek
	glTranslated(a + 2475, 320, 0.0);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();
	glPopMatrix();

	glPushMatrix();//arka tekerlek
	glTranslated(a + 2645, 320, 0.0);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();
	glPopMatrix();
}
void otobus3()
{
	glPushMatrix();
	glTranslated(a + 3000, 50.0, 0.0);
	glScaled(40.0, 40.0, 0.0);
	glColor3f(0.8, 0.3, 0.1);
	//otobus d���
	glBegin(GL_POLYGON);
	glVertex2f(25, 8);
	glVertex2f(25, 9.5);
	glVertex2f(26, 11);
	glVertex2f(32, 11);
	glVertex2f(32, 8);
	glEnd();
	//pencere �er�evesi
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(26.1, 9.5);
	glVertex2f(26.1, 10.5);
	glVertex2f(31.8, 10.5);
	glVertex2f(31.8, 9.5);
	glEnd();
	//kap�
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(26.2, 9);
	glVertex2f(26.2, 10.4);
	glVertex2f(27.7, 10.4);
	glVertex2f(27.7, 9);
	glEnd();

	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(27, 8.4);
	glVertex2f(27, 10.4);
	glVertex2f(27.7, 10.4);
	glVertex2f(27.7, 8.4);
	glEnd();
	//k���k pencere
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(27.8, 9.6);
	glVertex2f(27.8, 10.4);
	glVertex2f(29, 10.4);
	glVertex2f(29, 9.6);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(29.1, 9.6);
	glVertex2f(29.1, 10.4);
	glVertex2f(30.2, 10.4);
	glVertex2f(30.2, 9.6);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(30.3, 9.6);
	glVertex2f(30.3, 10.4);
	glVertex2f(31.7, 10.4);
	glVertex2f(31.7, 9.6);
	glEnd();

	//s�r�c� penceresi
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(25, 9.5);
	glVertex2f(26, 11);
	glVertex2f(26, 9.5);
	glEnd();
	glPopMatrix();
	//tekerlekler
	glPushMatrix();//�n tekerlek
	glTranslated(a + 3970, 320, 0.0);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();
	glPopMatrix();

	glPushMatrix();//arka tekerlek
	glTranslated(a + 4150, 320, 0.0);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();
	glPopMatrix();
}
void araba1()
{
	glPushMatrix(); //d�� �izgi i�in renk 
	glTranslated(b, 190.0, 0.0);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(0.2, 0, 0.7);
	glBegin(GL_POLYGON);
	glVertex2f(2.5, 2.5);
	glVertex2f(3.0, 3.5);
	glVertex2f(3.5, 3.75);
	glVertex2f(4.0, 4.0);
	glVertex2f(4.5, 4.0);
	glVertex2f(5.0, 3.75);
	glVertex2f(5.5, 3.5);
	glVertex2f(5.75, 3.0);
	glVertex2f(6.0, 2.5);
	glVertex2f(16.5, 2.5);
	glVertex2f(16.75, 3.0);
	glVertex2f(17.0, 3.5);
	glVertex2f(17.5, 3.75);
	glVertex2f(18.0, 4.0);
	glVertex2f(18.5, 4.0);
	glVertex2f(19.0, 3.75);
	glVertex2f(19.5, 3.5);
	glVertex2f(19.75, 3.0);
	glVertex2f(20.0, 2.5);
	glVertex2f(21.0, 2.5);
	glVertex2f(21.0, 4.0);
	glVertex2f(21.5, 4.0);
	glVertex2f(21.0, 4.5);
	glVertex2f(20.0, 5.0);
	glVertex2f(15.0, 5.0);
	glVertex2f(14.0, 5.5);
	glVertex2f(13.0, 6.0);
	glVertex2f(12.0, 6.5);
	glVertex2f(11.0, 7.0);
	glVertex2f(6.0, 7.0);
	glVertex2f(5.0, 6.5);
	glVertex2f(4.5, 6.25);
	glVertex2f(4.25, 6.0);
	glVertex2f(4.0, 5.75);
	glVertex2f(3.5, 5.5);
	glVertex2f(3.0, 5.5);
	glVertex2f(1.9, 5.45);
	glVertex2f(1.8, 5.4);
	glVertex2f(1.7, 5.35);
	glVertex2f(1.6, 5.3);
	glVertex2f(1.5, 5.25);
	glVertex2f(1.4, 5.15);
	glVertex2f(1.3, 5.0);
	glVertex2f(1.2, 4.85);
	glVertex2f(1.1, 4.7);
	glVertex2f(1.0, 4.3);
	glVertex2f(1.0, 3.2);
	glVertex2f(1.1, 3.05);
	glVertex2f(1.2, 2.9);
	glVertex2f(1.3, 2.9);
	glVertex2f(1.4, 2.75);
	glVertex2f(1.5, 2.65);
	glVertex2f(1.6, 2.6);
	glVertex2f(1.7, 2.55);
	glVertex2f(1.8, 2.5);
	glVertex2f(1.9, 2.45);
	glVertex2f(2.0, 2.5);
	glEnd();

	glColor3f(0, 1, 1); //pencere rengi
	glBegin(GL_POLYGON);
	glVertex2f(5.0, 5.0);
	glVertex2f(14.0, 5.0);
	glVertex2f(11.5, 6.5);
	glVertex2f(10.5, 6.75);
	glVertex2f(7.0, 6.75);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON); //arka tekerlek
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();

	glBegin(GL_POLYGON); //�n tekerlek
	glVertex2f(17.0, 2.5);
	glVertex2f(17.0, 2.6);
	glVertex2f(17.15, 3.1);
	glVertex2f(17.2, 3.2);
	glVertex2f(17.3, 3.35);
	glVertex2f(17.4, 3.4);
	glVertex2f(17.5, 3.45);
	glVertex2f(17.6, 3.55);
	glVertex2f(17.7, 3.6);
	glVertex2f(17.8, 3.63);
	glVertex2f(18.0, 3.65);
	glVertex2f(18.2, 3.7);
	glVertex2f(18.4, 3.7);
	glVertex2f(18.6, 3.65);
	glVertex2f(18.8, 3.55);
	glVertex2f(19.0, 3.45);
	glVertex2f(19.1, 3.4);
	glVertex2f(19.2, 3.25);
	glVertex2f(19.3, 3.2);
	glVertex2f(19.4, 3.0);

	glVertex2f(19.5, 2.5);
	glVertex2f(19.45, 2.15);
	glVertex2f(19.4, 1.9);
	glVertex2f(19.35, 1.8);
	glVertex2f(19.2, 1.6);
	glVertex2f(19.0, 1.5);
	glVertex2f(18.9, 1.4);
	glVertex2f(18.7, 1.3);
	glVertex2f(18.6, 1.27);
	glVertex2f(18.4, 1.25);
	glVertex2f(18.0, 1.25);
	glVertex2f(17.9, 1.3);
	glVertex2f(17.75, 1.35);
	glVertex2f(17.6, 1.4);
	glVertex2f(17.45, 1.55);
	glVertex2f(17.3, 1.7);
	glVertex2f(17.2, 1.8);
	glVertex2f(17.1, 2.2);
	glEnd();
	glPopMatrix();
}
void araba2()
{
	glPushMatrix();
	glTranslated(b - 2000, 190.0, 0.0);
	glScaled(20.0, 20.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(2.5, 2.5);
	glVertex2f(3.0, 3.5);
	glVertex2f(3.5, 3.75);
	glVertex2f(4.0, 4.0);
	glVertex2f(4.5, 4.0);
	glVertex2f(5.0, 3.75);
	glVertex2f(5.5, 3.5);
	glVertex2f(5.75, 3.0);
	glVertex2f(6.0, 2.5);
	glVertex2f(16.5, 2.5);
	glVertex2f(16.75, 3.0);
	glVertex2f(17.0, 3.5);
	glVertex2f(17.5, 3.75);
	glVertex2f(18.0, 4.0);
	glVertex2f(18.5, 4.0);
	glVertex2f(19.0, 3.75);
	glVertex2f(19.5, 3.5);
	glVertex2f(19.75, 3.0);
	glVertex2f(20.0, 2.5);
	glVertex2f(21.0, 2.5);
	glVertex2f(21.0, 4.0);
	glVertex2f(21.5, 4.0);
	glVertex2f(21.0, 4.5);
	glVertex2f(20.0, 5.0);
	glVertex2f(15.0, 5.0);
	glVertex2f(14.0, 5.5);
	glVertex2f(13.0, 6.0);
	glVertex2f(12.0, 6.5);
	glVertex2f(11.0, 7.0);
	glVertex2f(6.0, 7.0);
	glVertex2f(5.0, 6.5);
	glVertex2f(4.5, 6.25);
	glVertex2f(4.25, 6.0);
	glVertex2f(4.0, 5.75);
	glVertex2f(3.5, 5.5);
	glVertex2f(3.0, 5.5);
	glVertex2f(1.9, 5.45);
	glVertex2f(1.8, 5.4);
	glVertex2f(1.7, 5.35);
	glVertex2f(1.6, 5.3);
	glVertex2f(1.5, 5.25);
	glVertex2f(1.4, 5.15);
	glVertex2f(1.3, 5.0);
	glVertex2f(1.2, 4.85);
	glVertex2f(1.1, 4.7);
	glVertex2f(1.0, 4.3);
	glVertex2f(1.0, 3.2);
	glVertex2f(1.1, 3.05);
	glVertex2f(1.2, 2.9);
	glVertex2f(1.3, 2.9);
	glVertex2f(1.4, 2.75);
	glVertex2f(1.5, 2.65);
	glVertex2f(1.6, 2.6);
	glVertex2f(1.7, 2.55);
	glVertex2f(1.8, 2.5);
	glVertex2f(1.9, 2.45);
	glVertex2f(2.0, 2.5);
	glEnd();

	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(5.0, 5.0);
	glVertex2f(14.0, 5.0);
	glVertex2f(11.5, 6.5);
	glVertex2f(10.5, 6.75);
	glVertex2f(7.0, 6.75);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //araba d�� �izgi rengi
	glBegin(GL_LINE_LOOP);
	glVertex2f(2.5, 2.5);
	glVertex2f(3.0, 3.5);
	glVertex2f(3.5, 3.75);
	glVertex2f(4.0, 4.0);
	glVertex2f(4.5, 4.0);
	glVertex2f(5.0, 3.75);
	glVertex2f(5.5, 3.5);
	glVertex2f(5.75, 3.0);
	glVertex2f(6.0, 2.5);
	glVertex2f(16.5, 2.5);
	glVertex2f(16.75, 3.0);
	glVertex2f(17.0, 3.5);
	glVertex2f(17.5, 3.75);
	glVertex2f(18.0, 4.0);
	glVertex2f(18.5, 4.0);
	glVertex2f(19.0, 3.75);
	glVertex2f(19.5, 3.5);
	glVertex2f(19.75, 3.0);
	glVertex2f(20.0, 2.5);
	glVertex2f(21.0, 2.5);
	glVertex2f(21.0, 4.0);
	glVertex2f(21.5, 4.0);
	glVertex2f(21.0, 4.5);
	glVertex2f(20.0, 5.0);
	glVertex2f(15.0, 5.0);
	glVertex2f(14.0, 5.5);
	glVertex2f(13.0, 6.0);
	glVertex2f(12.0, 6.5);
	glVertex2f(11.0, 7.0);
	glVertex2f(6.0, 7.0);
	glVertex2f(5.0, 6.5);
	glVertex2f(4.5, 6.25);
	glVertex2f(4.25, 6.0);
	glVertex2f(4.0, 5.75);
	glVertex2f(3.5, 5.5);
	glVertex2f(3.0, 5.5);
	glVertex2f(1.9, 5.45);
	glVertex2f(1.8, 5.4);
	glVertex2f(1.7, 5.35);
	glVertex2f(1.6, 5.3);
	glVertex2f(1.5, 5.25);
	glVertex2f(1.4, 5.15);
	glVertex2f(1.3, 5.0);
	glVertex2f(1.2, 4.85);
	glVertex2f(1.1, 4.7);
	glVertex2f(1.0, 4.3);
	glVertex2f(1.0, 3.2);
	glVertex2f(1.1, 3.05);
	glVertex2f(1.2, 2.9);
	glVertex2f(1.3, 2.9);
	glVertex2f(1.4, 2.75);
	glVertex2f(1.5, 2.65);
	glVertex2f(1.6, 2.6);
	glVertex2f(1.7, 2.55);
	glVertex2f(1.8, 2.5);
	glVertex2f(1.9, 2.45);
	glVertex2f(2.0, 2.5);
	glEnd();

	glColor3f(0.0, 0.0, 0.0); //araba tasar�m� d�� �izgi rengi
	glBegin(GL_LINE_LOOP); // Belirlenen vertexler aras� cizgi cizer bir birine baglar, ortografik daki vertex ba�taki vertex e baglan�r
	glVertex2f(8.0, 3.0);
	glVertex2f(16.0, 3.0);
	glVertex2f(16.5, 3.5);
	glVertex2f(17.0, 4.0);
	glVertex2f(16.5, 4.25);
	glVertex2f(16.0, 4.5);
	glVertex2f(15.0, 4.5);
	glVertex2f(15.0, 5.0);
	glVertex2f(14.0, 5.0);
	glVertex2f(11.5, 6.5);
	glVertex2f(10.5, 6.75);
	glVertex2f(7.0, 6.75);
	glVertex2f(5.0, 5.0);
	glVertex2f(7.0, 5.0);
	glVertex2f(6.5, 4.5);
	glEnd();

	//d�� hat ba�lama
	glBegin(GL_LINES);
	glVertex2d(7.0, 5.0);
	glVertex2d(15.0, 5.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2d(15.0, 4.0);
	glVertex2d(17.0, 4.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2d(15.0, 3.5);
	glVertex2d(16.5, 3.5);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2d(15.0, 5.0);
	glVertex2d(14.0, 3.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2d(12.0, 5.0);
	glVertex2d(12.0, 6.2);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2d(7.0, 5.0);
	glVertex2d(7.0, 6.7);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(3.0, 2.5);
	glVertex2f(3.0, 2.6);
	glVertex2f(3.15, 3.1);
	glVertex2f(3.2, 3.2);
	glVertex2f(3.3, 3.35);
	glVertex2f(3.4, 3.4);
	glVertex2f(3.5, 3.45);
	glVertex2f(3.6, 3.55);
	glVertex2f(3.7, 3.6);
	glVertex2f(3.8, 3.63);
	glVertex2f(4.0, 3.65);
	glVertex2f(4.2, 3.7);
	glVertex2f(4.4, 3.7);
	glVertex2f(4.6, 3.65);
	glVertex2f(4.8, 3.55);
	glVertex2f(5.0, 3.45);
	glVertex2f(5.1, 3.4);
	glVertex2f(5.2, 3.25);
	glVertex2f(5.3, 3.2);
	glVertex2f(5.4, 3.0);
	glVertex2f(5.5, 2.5);

	glVertex2f(5.45, 2.15);
	glVertex2f(5.4, 1.9);
	glVertex2f(5.35, 1.8);
	glVertex2f(5.2, 1.6);
	glVertex2f(5.0, 1.5);
	glVertex2f(4.9, 1.4);
	glVertex2f(4.7, 1.3);
	glVertex2f(4.6, 1.27);
	glVertex2f(4.4, 1.25);
	glVertex2f(4.0, 1.25);
	glVertex2f(3.9, 1.3);
	glVertex2f(3.75, 1.35);
	glVertex2f(3.6, 1.4);
	glVertex2f(3.45, 1.55);
	glVertex2f(3.3, 1.7);
	glVertex2f(3.2, 1.8);
	glVertex2f(3.1, 2.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(17.0, 2.5);
	glVertex2f(17.0, 2.6);
	glVertex2f(17.15, 3.1);
	glVertex2f(17.2, 3.2);
	glVertex2f(17.3, 3.35);
	glVertex2f(17.4, 3.4);
	glVertex2f(17.5, 3.45);
	glVertex2f(17.6, 3.55);
	glVertex2f(17.7, 3.6);
	glVertex2f(17.8, 3.63);
	glVertex2f(18.0, 3.65);
	glVertex2f(18.2, 3.7);
	glVertex2f(18.4, 3.7);
	glVertex2f(18.6, 3.65);
	glVertex2f(18.8, 3.55);
	glVertex2f(19.0, 3.45);
	glVertex2f(19.1, 3.4);
	glVertex2f(19.2, 3.25);
	glVertex2f(19.3, 3.2);
	glVertex2f(19.4, 3.0);

	glVertex2f(19.5, 2.5);
	glVertex2f(19.45, 2.15);
	glVertex2f(19.4, 1.9);
	glVertex2f(19.35, 1.8);
	glVertex2f(19.2, 1.6);
	glVertex2f(19.0, 1.5);
	glVertex2f(18.9, 1.4);
	glVertex2f(18.7, 1.3);
	glVertex2f(18.6, 1.27);
	glVertex2f(18.4, 1.25);
	glVertex2f(18.0, 1.25);
	glVertex2f(17.9, 1.3);
	glVertex2f(17.75, 1.35);
	glVertex2f(17.6, 1.4);
	glVertex2f(17.45, 1.55);
	glVertex2f(17.3, 1.7);
	glVertex2f(17.2, 1.8);
	glVertex2f(17.1, 2.2);
	glEnd();
	glPopMatrix();
}
void ortografik()
//ortografik izd���m d�n���m� uygulama
{
	glMatrixMode(GL_PROJECTION);                //Matris y���n�n� (stack) belirleme
	glLoadIdentity();   // Yap�lm�� t�m d�n���mlerin geri al�nmas�n� sa�lar.
	gluOrtho2D(0.0, 1346.0, 0.0, 728.0); //iki boyutlu g�r�� peneresinin (clipping window) b�y�kl���n� belirler.
}
void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1346, 728); // Olu�turulan pencerenin boyutlar�n� belirler. 
	glutInitWindowPosition(0, 0); // Pencerenin konumlanaca�� yeri belirtir
	glutCreateWindow("Trafik isaretleri"); //Pencere sisteminde bir pencere olu�turur ve pencere ba�l���na parametresindeki metni yazar.

	//fonks.�a��r
	glutDisplayFunc(goruntu);
	glutKeyboardFunc(klavye);
	glutMouseFunc(mouse);
	ortografik();
	glutMainLoop(); // Bu i�lev sayesinde program kendisine gelecek olaylar� (event) dinlemeye ba�lar ve e�er tan�ml�ysa gelen olaya g�re tan�mlanm�� bir i�levi (callback) �al��t�r�r.
}

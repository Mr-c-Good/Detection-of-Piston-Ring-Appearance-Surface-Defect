// MFC����Dlg.cpp : ʵ���ļ�
#include "stdafx.h"
#include "MFC����.h"
#include "MFC����Dlg.h"
#include "afxdialogex.h"
#include<opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//-----------------------------------��ȫ�ֱ����������֡�--------------------------------------
//		������ȫ�ֱ���������
//-----------------------------------------------------------------------------------------------
CString strFilePath;
CString strFileName;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC����Dlg �Ի���
CMFC����Dlg::CMFC����Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC����Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC����Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC����Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC����Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC����Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC����Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFC����Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFC����Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFC����Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFC����Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFC����Dlg::OnBnClickedButton8)
	ON_EN_CHANGE(IDC_InputChar, &CMFC����Dlg::OnEnChangeInputchar)
END_MESSAGE_MAP()


// CMFC����Dlg ��Ϣ�������

BOOL CMFC����Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MAXIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFC����Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFC����Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFC����Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//��������
void lunkuo()
{
	Mat g_srcImage; 
	Mat g_srcImage1;
	Mat g_grayImage;
	Mat g_grayImage1;
	Mat g_grayImage2;
	Mat g_cannyMat_output;

	vector<vector<Point>> g_vContours;
	vector<Vec4i> g_vHierarchy;

	// ����Դͼ��
	g_srcImage = imread( "Mosaic_map/output_caijian.bmp", 1 );
	g_srcImage1 = imread( "Mosaic_map/output.bmp", 1 );

	// ת�ɻҶȲ�ģ��������
	cvtColor( g_srcImage, g_grayImage, COLOR_BGR2GRAY );
	//	blur( g_grayImage, g_grayImage, Size(3,3) );
	GaussianBlur( g_grayImage, g_grayImage, Size(9,9) ,0,0);


	Mat drawing = Mat::zeros(g_grayImage.rows, g_grayImage.cols, CV_8UC3);
	g_grayImage1 = g_grayImage > 80;
	g_grayImage2 = g_grayImage > 60;
	g_grayImage1=~g_grayImage1;
	g_grayImage2=~g_grayImage2;
	g_grayImage=g_grayImage1-g_grayImage2;
	g_grayImage=g_grayImage1-g_grayImage;
	//g_grayImage=~g_grayImage;
	Mat element=getStructuringElement(MORPH_RECT,Size(3,3));
	//Mat element1=getStructuringElement(MORPH_RECT,Size(15,15));
	//morphologyEx(g_grayImage,g_grayImage,MORPH_GRADIENT,element);
	//morphologyEx(g_grayImage,g_grayImage,MORPH_GRADIENT,element);


	morphologyEx(g_grayImage,g_grayImage,MORPH_DILATE,element);
	//	morphologyEx(g_grayImage,g_grayImage,MORPH_GRADIENT,element1);
	//https://blog.csdn.net/weixin_35738542/article/details/52198640
	//imshow("1",g_grayImage1);
	//imshow("2",g_grayImage2);
	//imshow("3",g_grayImage);
	//	g_grayImage=~g_grayImage;

	//imshow("la",g_grayImage);
	// Ѱ������
	findContours( g_grayImage, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

	// �������
	for( int i = 0; i< g_vContours.size(); i++ )
	{
		Scalar color = Scalar(255, 255, 0);//��ɫ
		drawContours( drawing, g_vContours, i, color, 4, 8, g_vHierarchy, 0, Point() );
	}
	//imshow("da",drawing);
	// ��ʾЧ��ͼ
	resize(drawing,drawing,Size(),1,1);
	Mat imageROI;
	//	imageROI=drawing(Range(350,0,g_srcImage1.cols,g_srcImage1.rows));
	imageROI = g_srcImage1(Rect(350, 0, drawing.cols, drawing.rows));

	addWeighted(imageROI,0.5,drawing,0.5,0.0,imageROI);  
	imwrite("Defect_map/lunkuo.bmp",g_srcImage1);
	waitKey(0);
}

//1���òü�����ͼƬ���ӿ촦���ٶȣ�
//Ԥ�����Ҷȣ���ֵ�˲�������ͼ�������ʧ��
//�˲�������Ҫ����ȡͼ�����������������ֻ�ʱ���������
//��ֵ�����������ھ������⣬�����ڲ�ͬ��ͼ�����п����в�ͬ�ĻҶ�ֵ
//0Ϊ��ɫ��255Ϊ��ɫ
//1.������
//�ȸ�ʴ������
//���ã��Ŵ��ѷ�͵��ܶ���������С���壬��ƽ���ϴ�����ı߽�ʱ�����ı������
//2.������
//�����ͺ�ʴ
//���ã��ų�С�ͺڶ���ͻ���˱�ԭͼ�����������������

//���ǳ���
void diaojiao()
{
	//�ֲ������Ķ���
	Mat g_srcImage;
	Mat g_srcImage1;
	Mat g_grayImage;
	Mat threshold_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//���òü�����ͼƬ
	g_srcImage = imread( "Mosaic_map/output_caijian.bmp", 1 );
	//�������յ�ͼƬ
	g_srcImage1 = imread( "Mosaic_map/output.bmp", 1 );
	//��ͼ����лҶȴ���
	cvtColor( g_srcImage, g_grayImage, COLOR_BGR2GRAY );
	//imshow("ls",g_grayImage);
	//ʹ�þ�ֵ�˲���ͼ����н���blur
	blur( g_grayImage, g_grayImage, Size(7,7) );

	// ʹ��Threshold����Ե
	threshold( g_grayImage, threshold_output,40 , 255, THRESH_BINARY );	
	//imshow("la",threshold_output);
	//	0������  1��ʮ�ֽ�����  2�� ��Բ
	Mat element=getStructuringElement(MORPH_RECT,Size(15,15));
	//������
	morphologyEx(threshold_output,threshold_output,MORPH_OPEN,element);
	//������
	morphologyEx(threshold_output,threshold_output,MORPH_CLOSE,element);
	//imshow("la",threshold_output);
	//��
	threshold_output=~threshold_output;
	//imshow("la",threshold_output);//�������ã�����Ϊ��ʾ

	findContours( threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );// �ҳ�����

	//�ֲ��������塪����������
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );
	vector<Point2f>center( contours.size() );
	vector<float>radius( contours.size() );

	// ����αƽ����� + ��ȡ���κ�Բ�α߽��

	//һ��ѭ�����������в���
	for( unsigned int i = 0; i < contours.size(); i++ )
	{ 
		//��ָ�����ȱƽ����������
		approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true ); 
		//����㼯�������棨up-right�����α߽�
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );
		//�Ը����� 2D�㼯��Ѱ����С����İ�ΧԲ�� 
		minEnclosingCircle( contours_poly[i], center[i], radius[i] );
	}

	// ����
	Mat drawing = Mat::zeros(  threshold_output.size(), CV_8UC3 );

	for( int unsigned i = 0; i<contours.size( ); i++ )
	{
		//����Ϊ����ɫ
		Scalar color = Scalar(0 ,255,255);
		//��������
		drawContours( drawing, contours_poly, i, color, 4, 8, vector<Vec4i>(), 0, Point() );
		//circle( drawing, center[i], (int)radius[i], color, 4, 8, 0 );//����Բ
		//����������ܳ�
		//�������
		double area = contourArea(contours[i]);
		//�����ܳ�
		double length = arcLength(contours[i], true);
		//����
		//�������
		area=area*(30.0/40.0*1.4)/100;
		//�ܳ�����
		length=length*(30.0/40.0*1.4)/10;
		//�����ļ�
		ofstream outfile;   
		//������Ϊdiaojiao_canshu.txt�ļ����洢����
		outfile.open("diaojiao_canshu.txt");
		//����������ʾ
		outfile<<"���Ϊ"<<area<<"mm2"<<endl; 
		//����������ʾ
		outfile<<"�ܳ�Ϊ"<<length<<"mm"<<endl;
		outfile.close();//�ر��ı�
	}
	//���ӣ���������ȱ�ݺۼ���ü�ͼƬ���е���
	addWeighted(drawing,0.5,g_srcImage,0.5,0.,g_srcImage); 
	//����һ������Ȥ������
	Mat imageROI;
	//���ü�����ͼƬ�Ϲ���ȱ�ݼ���������ԭͼƬ����
	//������Ȥ�������ڣ�350��0����
	imageROI = g_srcImage1(Rect(350, 0, drawing.cols, drawing.rows));
	//����
	addWeighted(imageROI,0.5,drawing,0.5,0.0,imageROI);  
	//��������ͼƬ�洢
	imwrite("Defect_map/diaojiao.bmp",g_srcImage1);
	//�ȴ�����
	waitKey(0);
}

//ѹ�˳���
void yashang()
{
	//�ֲ������Ķ���
	Mat g_srcImage;
	Mat g_srcImage1;
	Mat g_grayImage;
	Mat threshold_output;//������
	Mat threshold_output_1;//����
	Mat threshold_output_2;//��
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	//����ԭͼ��
	g_srcImage =  imread( "Mosaic_map/output_caijian.bmp", 1 );
	g_srcImage1 =  imread( "Mosaic_map/output.bmp", 1 );
	//��ͼ����лҶȴ���
	cvtColor( g_srcImage, g_grayImage, COLOR_BGR2GRAY );
	//ʹ�þ�ֵ�˲���ͼ����н���blur
	blur( g_grayImage, g_grayImage, Size(7,7) );
	// ���� ʹ��Threshold����Ե
	threshold( g_grayImage, threshold_output_1,70 , 255, THRESH_BINARY );
	//  ������ ʹ��Threshold����Ե
	threshold( g_grayImage, threshold_output,100 , 255, THRESH_BINARY );	
	//	0������  1��ʮ�ֽ�����  2�� ��Բ
	Mat element=getStructuringElement(MORPH_RECT,Size(3,3));
	//	0������  1��ʮ�ֽ�����  2�� ��Բ
	Mat element1=getStructuringElement(MORPH_RECT,Size(9,9));
	//�ã�9��9����������
	erode(threshold_output_1,threshold_output_1,element1);
	//��
	threshold_output=~threshold_output;
	//��
	threshold_output_1=~threshold_output_1;
	//����
	threshold_output_2=threshold_output-threshold_output_1;
	//�ã�3��3�����Ӷ�ȱ����������
	dilate(threshold_output_2,threshold_output_2,element);
	//imshow("������",threshold_output);//�������ã�����Ϊ��ʾ
	//imshow("����",threshold_output_1);//�������ã�����Ϊ��ʾ
	//imshow("��",threshold_output_2);//�������ã�����Ϊ��ʾ

	// �ҳ�����
	findContours( threshold_output_2, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

	//�ֲ��������塪����������
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );
	vector<Point2f>center( contours.size() );
	vector<float>radius( contours.size() );

	// ����αƽ����� + ��ȡ���κ�Բ�α߽��
	//һ��ѭ�����������в���
	for( unsigned int i = 0; i < contours.size(); i++ )
	{ 
		//��ָ�����ȱƽ���������� 
		approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
		//����㼯�������棨up-right�����α߽�
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );
		//�Ը����� 2D�㼯��Ѱ����С����İ�ΧԲ�� 
		minEnclosingCircle( contours_poly[i], center[i], radius[i] );
	}
	// ����
	Mat drawing = Mat::zeros(  threshold_output_2.size(), CV_8UC3 );

	for( int unsigned i = 0; i<contours.size( ); i++ )
	{
		//����Ϊ����ɫ
		Scalar color = Scalar(255,0,255);
		//��������
		drawContours( drawing, contours_poly, i, color, 2, 8, vector<Vec4i>(), 0, Point() );
		//circle( drawing, center[i], (int)radius[i], color, 4, 8, 0 );//����Բ
		addWeighted(g_srcImage,1,drawing,0.8,0.,g_srcImage);  
		//imshow("zui",g_srcImage);
	}
	addWeighted(drawing,1,g_srcImage,0.5,0.,g_srcImage);  

	Mat imageROI;
	imageROI = g_srcImage1(Rect(350, 0, drawing.cols, drawing.rows));
	addWeighted(imageROI,0.5,drawing,0.5,0.0,imageROI);  
	imwrite("Defect_map/huaheng.bmp",g_srcImage1);
	waitKey(0);
}

//ͼƬ�ɼ�
void CMFC����Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


//ͼƬ�ü�
void CMFC����Dlg::OnBnClickedButton2()
{
	//��ȡλ��Mosaic_map/output.bmp��ͼƬ
	Mat image1=  imread( "Mosaic_map/output.bmp");
	//����һ������Ȥ����
	Mat imageROI;
	//���Ͻ�����(350,0)�����½����꣨550��850���ľ���
	imageROI=image1(Rect(350,0,550,850));
	//imshow("�ü�",imageROI);//��ʾ�ü����򣬵����п��Բ鿴����ʽ�����в�����
	//�ȴ�����
	waitKey(0); 	
	//��������ͼƬд�뵽Mosaic_map/output_caijian.bmp��
	imwrite("Mosaic_map/output_caijian.bmp",imageROI);
	//��ȡͼƬ·����ͼƬ����
	strFilePath = "Mosaic_map/output_caijian.bmp";

	CImage image;
	image.Load(strFilePath);

	//��������������Ҫ�����ǣ���ȡ�Ի��������Picture Control��width��height��
	//�����õ�ͼƬ����rectPicture������ͼƬ����rectPicture��ͼƬ���д���
	//������ͼƬ���Ի�����Picture Control����

	//�ؼ����ζ���
	CRect rectControl;    
	//ͼƬ���ζ���
	CRect rectPicture;                       

	int x = image.GetWidth();
	int y = image.GetHeight();

	//Picture Control��IDΪIDC_Src
	CWnd  *pWnd = GetDlgItem(IDC_dst);
	pWnd->GetClientRect(rectControl);

	CDC *pDc = GetDlgItem(IDC_dst)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

	((CStatic*)GetDlgItem(IDC_dst))->SetBitmap(NULL);

	//�������ַ������ɻ���ͼƬ
	//��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������
	//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); 
	//��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������
	image.Draw(pDc->m_hDC, rectPicture);    

	image.Destroy();
	pWnd->ReleaseDC(pDc);

}


//������ʾ
void CMFC����Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	lunkuo();

	//��ȡͼƬ·����ͼƬ����
	strFilePath = "Defect_map/lunkuo.bmp";

	CImage image;
	image.Load(strFilePath);

	//��������������Ҫ�����ǣ���ȡ�Ի��������Picture Control��width��height��
	//�����õ�ͼƬ����rectPicture������ͼƬ����rectPicture��ͼƬ���д���
	//������ͼƬ���Ի�����Picture Control����

	//�ؼ����ζ���
	CRect rectControl; 
	//ͼƬ���ζ���
	CRect rectPicture;                        

	int x = image.GetWidth();
	int y = image.GetHeight();

	//Picture Control��IDΪIDC_Src
	CWnd  *pWnd = GetDlgItem(IDC_Src);
	pWnd->GetClientRect(rectControl);

	CDC *pDc = GetDlgItem(IDC_Src)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

	((CStatic*)GetDlgItem(IDC_Src))->SetBitmap(NULL);

	//�������ַ������ɻ���ͼƬ
	//��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������
	//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); 
	//��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������
	image.Draw(pDc->m_hDC, rectPicture);                

	image.Destroy();
	pWnd->ReleaseDC(pDc);
}

//ȱ�ݼ��
void CMFC����Dlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Mat dj,hh;

	diaojiao();
	yashang();

	dj=imread("Defect_map/diaojiao.bmp");
	hh=imread("Defect_map/huaheng.bmp");
	addWeighted(dj,0.8,hh,0.8,0.,dj);  
	imwrite("Defect_map/zong.bmp",dj);

	//��ȡͼƬ·����ͼƬ����
	strFilePath = "Defect_map/zong.bmp";

	CImage image;
	image.Load(strFilePath);

	//��������������Ҫ�����ǣ���ȡ�Ի��������Picture Control��width��height��
	//�����õ�ͼƬ����rectPicture������ͼƬ����rectPicture��ͼƬ���д���
	//������ͼƬ���Ի�����Picture Control����

	//�ؼ����ζ���
	CRect rectControl;           
	//ͼƬ���ζ���
	CRect rectPicture;                     

	int x = image.GetWidth();
	int y = image.GetHeight();

	//Picture Control��IDΪIDC_Src
	CWnd  *pWnd = GetDlgItem(IDC_Src);
	pWnd->GetClientRect(rectControl);

	CDC *pDc = GetDlgItem(IDC_Src)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

	((CStatic*)GetDlgItem(IDC_Src))->SetBitmap(NULL);

	//�������ַ������ɻ���ͼƬ
	//��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������
	//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); 
	//��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������
	image.Draw(pDc->m_hDC, rectPicture);               

	image.Destroy();
	pWnd->ReleaseDC(pDc);


}

//
void CMFC����Dlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}

//ѹ��ȱ����ʾ
void CMFC����Dlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ȡͼƬ·����ͼƬ����
	strFilePath = "Defect_map/huaheng.bmp";


	CImage image;
	image.Load(strFilePath);

	//��������������Ҫ�����ǣ���ȡ�Ի��������Picture Control��width��height��
	//�����õ�ͼƬ����rectPicture������ͼƬ����rectPicture��ͼƬ���д���
	//������ͼƬ���Ի�����Picture Control����

	//�ؼ����ζ���
	CRect rectControl;      
	//ͼƬ���ζ���
	CRect rectPicture;                       

	int x = image.GetWidth();
	int y = image.GetHeight();

	//Picture Control��IDΪIDC_Src
	CWnd  *pWnd = GetDlgItem(IDC_Src);
	pWnd->GetClientRect(rectControl);

	CDC *pDc = GetDlgItem(IDC_Src)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

	((CStatic*)GetDlgItem(IDC_Src))->SetBitmap(NULL);

	//�������ַ������ɻ���ͼƬ
	//��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������
	//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); 
	//��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������
	image.Draw(pDc->m_hDC, rectPicture);                
	image.Destroy();
	pWnd->ReleaseDC(pDc);
}


//	����ȱ����ʾ
void CMFC����Dlg::OnBnClickedButton7()
{
	//��ȡͼƬ·����ͼƬ����
	strFilePath = "Defect_map/diaojiao.bmp";

	CImage image;
	image.Load(strFilePath);

	//��������������Ҫ�����ǣ���ȡ�Ի��������Picture Control��width��height��
	//�����õ�ͼƬ����rectPicture������ͼƬ����rectPicture��ͼƬ���д���
	//������ͼƬ���Ի�����Picture Control����

	//�ؼ����ζ���
	CRect rectControl;      
	//ͼƬ���ζ���
	CRect rectPicture;                       

	int x = image.GetWidth();
	int y = image.GetHeight();

	//Picture Control��IDΪIDC_Src
	CWnd  *pWnd = GetDlgItem(IDC_Src);
	pWnd->GetClientRect(rectControl);

	CDC *pDc = GetDlgItem(IDC_Src)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

	((CStatic*)GetDlgItem(IDC_Src))->SetBitmap(NULL);

	//�������ַ������ɻ���ͼƬ
	//��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������
	//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); 
	//��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������
	image.Draw(pDc->m_hDC, rectPicture);               

	image.Destroy();
	pWnd->ReleaseDC(pDc);


	CString str;
	GetDlgItem(IDC_InputChar)->GetWindowText(str);
	ShellExecute(NULL, _T("open"), _T("diaojiao_canshu.txt"), NULL, NULL, SW_SHOW);

}

//ѡ��ͼƬ
void CMFC����Dlg::OnBnClickedButton8()
{
	//�ο� https://blog.csdn.net/XuePiaoFei1/article/details/78071471
	//ѡ��ͼƬ
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 0, _T("image Files(*.bmp; *.jpg;*.png)|*.JPG;*.PNG;*.BMP|All Files (*.*) |*.*||"), this);
	fileDlg.DoModal();

	//��ȡͼƬ·����ͼƬ����
	//·��
	strFilePath = fileDlg.GetPathName();
	//����
	strFileName = fileDlg.GetFileName();

	//�ж�·����Ϊ��
	if (strFilePath == _T(""))
	{
		return;
	}
	CImage image;
	image.Load(strFilePath);//����

	//��������������Ҫ�����ǣ���ȡ�Ի��������Picture Control��width��height��
	//�����õ�ͼƬ����rectPicture������ͼƬ����rectPicture��ͼƬ���д���
	//������ͼƬ���Ի�����Picture Control����

	//�ؼ����ζ���
	CRect rectControl;     
	//ͼƬ���ζ���
	CRect rectPicture;  

	//����xΪ���
	int x = image.GetWidth();
	//����yΪ�߶�
	int y = image.GetHeight();

	//Picture Control��IDΪIDC_Src
	CWnd  *pWnd = GetDlgItem(IDC_Src);
	pWnd->GetClientRect(rectControl);

	CDC *pDc = GetDlgItem(IDC_Src)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

	((CStatic*)GetDlgItem(IDC_Src))->SetBitmap(NULL);

	//�������ַ������ɻ���ͼƬ
	//��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������
	//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); 
	//��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������
	image.Draw(pDc->m_hDC, rectPicture);                

	image.Destroy();
	pWnd->ReleaseDC(pDc);
	//--------------------------------------------------------------------------------
	//�ο� https://blog.csdn.net/a478257115/article/details/53031799
	//����
	CWnd* bmpShow = GetDlgItem(IDC_Src);
	CDC *pdc = bmpShow->GetDC();
	CImage  imag;
	CRect rect;
	CString picturePath;

	 //��ȡ������С
	GetClientRect(&rect);       
	bmpShow->GetWindowRect(&rect);
	imag.Create(rect.Width(), rect.Height(), 32);
	::BitBlt(imag.GetDC(), 0, 0, rect.Width(), rect.Height(), pdc->m_hDC, 0, 0, SRCCOPY);

	 //�ļ�·��
	picturePath = "Mosaic_map/output.bmp"; 
	//����ͼƬ
	HRESULT hResult = imag.Save(picturePath); 
	ReleaseDC(pdc);
	imag.ReleaseDC();
}

void CMFC����Dlg::OnEnChangeInputchar()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
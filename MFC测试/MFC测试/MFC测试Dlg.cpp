// MFC测试Dlg.cpp : 实现文件
#include "stdafx.h"
#include "MFC测试.h"
#include "MFC测试Dlg.h"
#include "afxdialogex.h"
#include<opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//-----------------------------------【全局变量声明部分】--------------------------------------
//		描述：全局变量的声明
//-----------------------------------------------------------------------------------------------
CString strFilePath;
CString strFileName;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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


// CMFC测试Dlg 对话框
CMFC测试Dlg::CMFC测试Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC测试Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC测试Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC测试Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC测试Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC测试Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC测试Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFC测试Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFC测试Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFC测试Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFC测试Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFC测试Dlg::OnBnClickedButton8)
	ON_EN_CHANGE(IDC_InputChar, &CMFC测试Dlg::OnEnChangeInputchar)
END_MESSAGE_MAP()


// CMFC测试Dlg 消息处理程序

BOOL CMFC测试Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MAXIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC测试Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC测试Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFC测试Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//轮廓程序
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

	// 加载源图像
	g_srcImage = imread( "Mosaic_map/output_caijian.bmp", 1 );
	g_srcImage1 = imread( "Mosaic_map/output.bmp", 1 );

	// 转成灰度并模糊化降噪
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
	// 寻找轮廓
	findContours( g_grayImage, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

	// 绘出轮廓
	for( int i = 0; i< g_vContours.size(); i++ )
	{
		Scalar color = Scalar(255, 255, 0);//青色
		drawContours( drawing, g_vContours, i, color, 4, 8, g_vHierarchy, 0, Point() );
	}
	//imshow("da",drawing);
	// 显示效果图
	resize(drawing,drawing,Size(),1,1);
	Mat imageROI;
	//	imageROI=drawing(Range(350,0,g_srcImage1.cols,g_srcImage1.rows));
	imageROI = g_srcImage1(Rect(350, 0, drawing.cols, drawing.rows));

	addWeighted(imageROI,0.5,drawing,0.5,0.0,imageROI);  
	imwrite("Defect_map/lunkuo.bmp",g_srcImage1);
	waitKey(0);
}

//1调用裁剪过的图片，加快处理速度；
//预处理，灰度，均值滤波，减少图像的噪点和失真
//滤波处理主要是提取图像特征或者消除数字化时混入的噪声
//二值化处理，依赖于具体问题，物体在不同的图像中有可能有不同的灰度值
//0为黑色，255为白色
//1.开运算
//先腐蚀后膨胀
//作用：放大裂缝和低密度区域，消除小物体，在平滑较大物体的边界时，不改变其面积
//2.闭运算
//先膨胀后腐蚀
//作用：排除小型黑洞，突触了比原图轮廓区域更暗的区域

//掉角程序
void diaojiao()
{
	//局部变量的定义
	Mat g_srcImage;
	Mat g_srcImage1;
	Mat g_grayImage;
	Mat threshold_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//调用裁剪过的图片
	g_srcImage = imread( "Mosaic_map/output_caijian.bmp", 1 );
	//调用最终的图片
	g_srcImage1 = imread( "Mosaic_map/output.bmp", 1 );
	//对图像进行灰度处理
	cvtColor( g_srcImage, g_grayImage, COLOR_BGR2GRAY );
	//imshow("ls",g_grayImage);
	//使用均值滤波对图像进行降噪blur
	blur( g_grayImage, g_grayImage, Size(7,7) );

	// 使用Threshold检测边缘
	threshold( g_grayImage, threshold_output,40 , 255, THRESH_BINARY );	
	//imshow("la",threshold_output);
	//	0：矩形  1：十字交叉形  2： 椭圆
	Mat element=getStructuringElement(MORPH_RECT,Size(15,15));
	//开运算
	morphologyEx(threshold_output,threshold_output,MORPH_OPEN,element);
	//闭运算
	morphologyEx(threshold_output,threshold_output,MORPH_CLOSE,element);
	//imshow("la",threshold_output);
	//求反
	threshold_output=~threshold_output;
	//imshow("la",threshold_output);//程序检测用，可作为显示

	findContours( threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );// 找出轮廓

	//局部变量定义——向量变量
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );
	vector<Point2f>center( contours.size() );
	vector<float>radius( contours.size() );

	// 多边形逼近轮廓 + 获取矩形和圆形边界框

	//一个循环，遍历所有部分
	for( unsigned int i = 0; i < contours.size(); i++ )
	{ 
		//用指定精度逼近多边形曲线
		approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true ); 
		//计算点集的最外面（up-right）矩形边界
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );
		//对给定的 2D点集，寻找最小面积的包围圆形 
		minEnclosingCircle( contours_poly[i], center[i], radius[i] );
	}

	// 绘制
	Mat drawing = Mat::zeros(  threshold_output.size(), CV_8UC3 );

	for( int unsigned i = 0; i<contours.size( ); i++ )
	{
		//设置为黄颜色
		Scalar color = Scalar(0 ,255,255);
		//绘制轮廓
		drawContours( drawing, contours_poly, i, color, 4, 8, vector<Vec4i>(), 0, Point() );
		//circle( drawing, center[i], (int)radius[i], color, 4, 8, 0 );//绘制圆
		//计算面积与周长
		//计算面积
		double area = contourArea(contours[i]);
		//计算周长
		double length = arcLength(contours[i], true);
		//计算
		//面积计算
		area=area*(30.0/40.0*1.4)/100;
		//周长计算
		length=length*(30.0/40.0*1.4)/10;
		//创建文件
		ofstream outfile;   
		//创建名为diaojiao_canshu.txt文件，存储数据
		outfile.open("diaojiao_canshu.txt");
		//数据流的显示
		outfile<<"面积为"<<area<<"mm2"<<endl; 
		//数据流的显示
		outfile<<"周长为"<<length<<"mm"<<endl;
		outfile.close();//关闭文本
	}
	//叠加，将检测出的缺陷痕迹与裁剪图片进行叠加
	addWeighted(drawing,0.5,g_srcImage,0.5,0.,g_srcImage); 
	//定义一个感兴趣的区域
	Mat imageROI;
	//将裁剪过的图片上关于缺陷检测的数据与原图片叠加
	//将感兴趣区域定义在（350，0）处
	imageROI = g_srcImage1(Rect(350, 0, drawing.cols, drawing.rows));
	//叠加
	addWeighted(imageROI,0.5,drawing,0.5,0.0,imageROI);  
	//将处理后的图片存储
	imwrite("Defect_map/diaojiao.bmp",g_srcImage1);
	//等待结束
	waitKey(0);
}

//压伤程序
void yashang()
{
	//局部变量的定义
	Mat g_srcImage;
	Mat g_srcImage1;
	Mat g_grayImage;
	Mat threshold_output;//被减数
	Mat threshold_output_1;//减数
	Mat threshold_output_2;//差
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	//载入原图像
	g_srcImage =  imread( "Mosaic_map/output_caijian.bmp", 1 );
	g_srcImage1 =  imread( "Mosaic_map/output.bmp", 1 );
	//对图像进行灰度处理
	cvtColor( g_srcImage, g_grayImage, COLOR_BGR2GRAY );
	//使用均值滤波对图像进行降噪blur
	blur( g_grayImage, g_grayImage, Size(7,7) );
	// 减数 使用Threshold检测边缘
	threshold( g_grayImage, threshold_output_1,70 , 255, THRESH_BINARY );
	//  被减数 使用Threshold检测边缘
	threshold( g_grayImage, threshold_output,100 , 255, THRESH_BINARY );	
	//	0：矩形  1：十字交叉形  2： 椭圆
	Mat element=getStructuringElement(MORPH_RECT,Size(3,3));
	//	0：矩形  1：十字交叉形  2： 椭圆
	Mat element1=getStructuringElement(MORPH_RECT,Size(9,9));
	//用（9，9）算子膨胀
	erode(threshold_output_1,threshold_output_1,element1);
	//求反
	threshold_output=~threshold_output;
	//求反
	threshold_output_1=~threshold_output_1;
	//运算
	threshold_output_2=threshold_output-threshold_output_1;
	//用（3，3）算子对缺陷特征膨胀
	dilate(threshold_output_2,threshold_output_2,element);
	//imshow("被减数",threshold_output);//程序检测用，可作为显示
	//imshow("减数",threshold_output_1);//程序检测用，可作为显示
	//imshow("差",threshold_output_2);//程序检测用，可作为显示

	// 找出轮廓
	findContours( threshold_output_2, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

	//局部变量定义——向量变量
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );
	vector<Point2f>center( contours.size() );
	vector<float>radius( contours.size() );

	// 多边形逼近轮廓 + 获取矩形和圆形边界框
	//一个循环，遍历所有部分
	for( unsigned int i = 0; i < contours.size(); i++ )
	{ 
		//用指定精度逼近多边形曲线 
		approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
		//计算点集的最外面（up-right）矩形边界
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );
		//对给定的 2D点集，寻找最小面积的包围圆形 
		minEnclosingCircle( contours_poly[i], center[i], radius[i] );
	}
	// 绘制
	Mat drawing = Mat::zeros(  threshold_output_2.size(), CV_8UC3 );

	for( int unsigned i = 0; i<contours.size( ); i++ )
	{
		//设置为粉颜色
		Scalar color = Scalar(255,0,255);
		//绘制轮廓
		drawContours( drawing, contours_poly, i, color, 2, 8, vector<Vec4i>(), 0, Point() );
		//circle( drawing, center[i], (int)radius[i], color, 4, 8, 0 );//绘制圆
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

//图片采集
void CMFC测试Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

}


//图片裁剪
void CMFC测试Dlg::OnBnClickedButton2()
{
	//读取位于Mosaic_map/output.bmp的图片
	Mat image1=  imread( "Mosaic_map/output.bmp");
	//定义一个感兴趣区域
	Mat imageROI;
	//左上角坐标(350,0)到右下角坐标（550，850）的矩形
	imageROI=image1(Rect(350,0,550,850));
	//imshow("裁剪",imageROI);//显示裁剪区域，调试中可以查看，正式程序中不采用
	//等待按下
	waitKey(0); 	
	//将处理后的图片写入到Mosaic_map/output_caijian.bmp处
	imwrite("Mosaic_map/output_caijian.bmp",imageROI);
	//获取图片路径和图片名称
	strFilePath = "Mosaic_map/output_caijian.bmp";

	CImage image;
	image.Load(strFilePath);

	//以下两个矩形主要作用是，获取对话框上面的Picture Control的width和height，
	//并设置到图片矩形rectPicture，根据图片矩形rectPicture对图片进行处理，
	//最后绘制图片到对话框上Picture Control上面

	//控件矩形对象
	CRect rectControl;    
	//图片矩形对象
	CRect rectPicture;                       

	int x = image.GetWidth();
	int y = image.GetHeight();

	//Picture Control的ID为IDC_Src
	CWnd  *pWnd = GetDlgItem(IDC_dst);
	pWnd->GetClientRect(rectControl);

	CDC *pDc = GetDlgItem(IDC_dst)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

	((CStatic*)GetDlgItem(IDC_dst))->SetBitmap(NULL);

	//以下两种方法都可绘制图片
	//将图片绘制到Picture控件表示的矩形区域
	//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); 
	//将图片绘制到Picture控件表示的矩形区域
	image.Draw(pDc->m_hDC, rectPicture);    

	image.Destroy();
	pWnd->ReleaseDC(pDc);

}


//轮廓显示
void CMFC测试Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	lunkuo();

	//获取图片路径和图片名称
	strFilePath = "Defect_map/lunkuo.bmp";

	CImage image;
	image.Load(strFilePath);

	//以下两个矩形主要作用是，获取对话框上面的Picture Control的width和height，
	//并设置到图片矩形rectPicture，根据图片矩形rectPicture对图片进行处理，
	//最后绘制图片到对话框上Picture Control上面

	//控件矩形对象
	CRect rectControl; 
	//图片矩形对象
	CRect rectPicture;                        

	int x = image.GetWidth();
	int y = image.GetHeight();

	//Picture Control的ID为IDC_Src
	CWnd  *pWnd = GetDlgItem(IDC_Src);
	pWnd->GetClientRect(rectControl);

	CDC *pDc = GetDlgItem(IDC_Src)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

	((CStatic*)GetDlgItem(IDC_Src))->SetBitmap(NULL);

	//以下两种方法都可绘制图片
	//将图片绘制到Picture控件表示的矩形区域
	//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); 
	//将图片绘制到Picture控件表示的矩形区域
	image.Draw(pDc->m_hDC, rectPicture);                

	image.Destroy();
	pWnd->ReleaseDC(pDc);
}

//缺陷检测
void CMFC测试Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat dj,hh;

	diaojiao();
	yashang();

	dj=imread("Defect_map/diaojiao.bmp");
	hh=imread("Defect_map/huaheng.bmp");
	addWeighted(dj,0.8,hh,0.8,0.,dj);  
	imwrite("Defect_map/zong.bmp",dj);

	//获取图片路径和图片名称
	strFilePath = "Defect_map/zong.bmp";

	CImage image;
	image.Load(strFilePath);

	//以下两个矩形主要作用是，获取对话框上面的Picture Control的width和height，
	//并设置到图片矩形rectPicture，根据图片矩形rectPicture对图片进行处理，
	//最后绘制图片到对话框上Picture Control上面

	//控件矩形对象
	CRect rectControl;           
	//图片矩形对象
	CRect rectPicture;                     

	int x = image.GetWidth();
	int y = image.GetHeight();

	//Picture Control的ID为IDC_Src
	CWnd  *pWnd = GetDlgItem(IDC_Src);
	pWnd->GetClientRect(rectControl);

	CDC *pDc = GetDlgItem(IDC_Src)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

	((CStatic*)GetDlgItem(IDC_Src))->SetBitmap(NULL);

	//以下两种方法都可绘制图片
	//将图片绘制到Picture控件表示的矩形区域
	//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); 
	//将图片绘制到Picture控件表示的矩形区域
	image.Draw(pDc->m_hDC, rectPicture);               

	image.Destroy();
	pWnd->ReleaseDC(pDc);


}

//
void CMFC测试Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

}

//压伤缺陷显示
void CMFC测试Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码

	//获取图片路径和图片名称
	strFilePath = "Defect_map/huaheng.bmp";


	CImage image;
	image.Load(strFilePath);

	//以下两个矩形主要作用是，获取对话框上面的Picture Control的width和height，
	//并设置到图片矩形rectPicture，根据图片矩形rectPicture对图片进行处理，
	//最后绘制图片到对话框上Picture Control上面

	//控件矩形对象
	CRect rectControl;      
	//图片矩形对象
	CRect rectPicture;                       

	int x = image.GetWidth();
	int y = image.GetHeight();

	//Picture Control的ID为IDC_Src
	CWnd  *pWnd = GetDlgItem(IDC_Src);
	pWnd->GetClientRect(rectControl);

	CDC *pDc = GetDlgItem(IDC_Src)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

	((CStatic*)GetDlgItem(IDC_Src))->SetBitmap(NULL);

	//以下两种方法都可绘制图片
	//将图片绘制到Picture控件表示的矩形区域
	//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); 
	//将图片绘制到Picture控件表示的矩形区域
	image.Draw(pDc->m_hDC, rectPicture);                
	image.Destroy();
	pWnd->ReleaseDC(pDc);
}


//	掉角缺陷显示
void CMFC测试Dlg::OnBnClickedButton7()
{
	//获取图片路径和图片名称
	strFilePath = "Defect_map/diaojiao.bmp";

	CImage image;
	image.Load(strFilePath);

	//以下两个矩形主要作用是，获取对话框上面的Picture Control的width和height，
	//并设置到图片矩形rectPicture，根据图片矩形rectPicture对图片进行处理，
	//最后绘制图片到对话框上Picture Control上面

	//控件矩形对象
	CRect rectControl;      
	//图片矩形对象
	CRect rectPicture;                       

	int x = image.GetWidth();
	int y = image.GetHeight();

	//Picture Control的ID为IDC_Src
	CWnd  *pWnd = GetDlgItem(IDC_Src);
	pWnd->GetClientRect(rectControl);

	CDC *pDc = GetDlgItem(IDC_Src)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

	((CStatic*)GetDlgItem(IDC_Src))->SetBitmap(NULL);

	//以下两种方法都可绘制图片
	//将图片绘制到Picture控件表示的矩形区域
	//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); 
	//将图片绘制到Picture控件表示的矩形区域
	image.Draw(pDc->m_hDC, rectPicture);               

	image.Destroy();
	pWnd->ReleaseDC(pDc);


	CString str;
	GetDlgItem(IDC_InputChar)->GetWindowText(str);
	ShellExecute(NULL, _T("open"), _T("diaojiao_canshu.txt"), NULL, NULL, SW_SHOW);

}

//选择图片
void CMFC测试Dlg::OnBnClickedButton8()
{
	//参考 https://blog.csdn.net/XuePiaoFei1/article/details/78071471
	//选择图片
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 0, _T("image Files(*.bmp; *.jpg;*.png)|*.JPG;*.PNG;*.BMP|All Files (*.*) |*.*||"), this);
	fileDlg.DoModal();

	//获取图片路径和图片名称
	//路径
	strFilePath = fileDlg.GetPathName();
	//名称
	strFileName = fileDlg.GetFileName();

	//判断路径不为空
	if (strFilePath == _T(""))
	{
		return;
	}
	CImage image;
	image.Load(strFilePath);//载入

	//以下两个矩形主要作用是，获取对话框上面的Picture Control的width和height，
	//并设置到图片矩形rectPicture，根据图片矩形rectPicture对图片进行处理，
	//最后绘制图片到对话框上Picture Control上面

	//控件矩形对象
	CRect rectControl;     
	//图片矩形对象
	CRect rectPicture;  

	//定义x为宽度
	int x = image.GetWidth();
	//定义y为高度
	int y = image.GetHeight();

	//Picture Control的ID为IDC_Src
	CWnd  *pWnd = GetDlgItem(IDC_Src);
	pWnd->GetClientRect(rectControl);

	CDC *pDc = GetDlgItem(IDC_Src)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(), CSize((int)rectControl.Width(), (int)rectControl.Height()));

	((CStatic*)GetDlgItem(IDC_Src))->SetBitmap(NULL);

	//以下两种方法都可绘制图片
	//将图片绘制到Picture控件表示的矩形区域
	//image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); 
	//将图片绘制到Picture控件表示的矩形区域
	image.Draw(pDc->m_hDC, rectPicture);                

	image.Destroy();
	pWnd->ReleaseDC(pDc);
	//--------------------------------------------------------------------------------
	//参考 https://blog.csdn.net/a478257115/article/details/53031799
	//保存
	CWnd* bmpShow = GetDlgItem(IDC_Src);
	CDC *pdc = bmpShow->GetDC();
	CImage  imag;
	CRect rect;
	CString picturePath;

	 //获取画布大小
	GetClientRect(&rect);       
	bmpShow->GetWindowRect(&rect);
	imag.Create(rect.Width(), rect.Height(), 32);
	::BitBlt(imag.GetDC(), 0, 0, rect.Width(), rect.Height(), pdc->m_hDC, 0, 0, SRCCOPY);

	 //文件路径
	picturePath = "Mosaic_map/output.bmp"; 
	//保存图片
	HRESULT hResult = imag.Save(picturePath); 
	ReleaseDC(pdc);
	imag.ReleaseDC();
}

void CMFC测试Dlg::OnEnChangeInputchar()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码
}
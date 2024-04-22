// opencv_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat image = imread("image.jpg");
    if (image.empty()) {
        cout << "ERROR" << endl;
        return -1;
    }
    Mat contour_image = Mat::zeros(image.size(), CV_8UC3);

    Mat gray, blurred, edges;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, blurred, Size(5, 5), 0);
    Canny(blurred, edges, 120, 240);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(edges.clone(), contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
    for (int i = 0; i < contours.size(); i++)
    {
        Scalar color(0, 255, 0);
        drawContours(contour_image, contours, i, color, 2, LINE_8, hierarchy, 0);
    }
    imshow("original", image);
    imshow("Text Contours", contour_image);
    waitKey(0);
    contours.clear();
    hierarchy.clear();
    Mat image2 = imread("image2.png");
    if (image2.empty()) {
        cout << "ERROR" << endl;
        return -1;
    }
    GaussianBlur(image2, blurred, Size(5, 5), 0);
    Canny(blurred, edges, 50, 150);
    findContours(edges.clone(), contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    Mat contour_image2 = Mat::zeros(image2.size(), CV_8UC3);
    
    for (int i = 0; i < contours.size(); i++) {
        vector<Point> approxCurve;
        approxPolyDP(contours[i], approxCurve, 0.03 * arcLength(contours[i], true), true);
        drawContours(contour_image2, contours, static_cast<int>(i), Scalar(255, 0, 0), 2);
        int verticesCount = approxCurve.size();
        string Name;
        if (verticesCount == 3)
            Name = "triangle";
        else if (verticesCount == 4)
            Name = "square";
        else
            Name = "circle";
        Moments mu = moments(contours[i]);
        Point centroid(mu.m10 / mu.m00, mu.m01 / mu.m00);
        putText(contour_image2, Name, centroid, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
    }
    imshow("Contours", contour_image2);
    waitKey(0);

    return 0;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

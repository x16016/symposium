//0821
//最頻値を利用
//ビーズのサイズの変更　be_size


#include <iostream>
#include <opencv2/opencv.hpp>


//ウィンドウ名
#define WINDOW_NAME_OUTPUT "finImage"
#define WINDOW_NAME_OUTPUT2 "resultImage"
#define WINDOW_NAME_OUTPUT3 "FcaceresultImage"


cv::CascadeClassifier faceClassifier;               //顔認識用分類器


int main(int argc, const char * argv[]) {
    
    //画像ファイルの読み込み
    cv::Mat source_img = cv::imread("007.png", cv::IMREAD_COLOR);
    if (source_img.data==0) {  //画像ファイルが読み込めなかった場合
        printf("File not found\n");
        exit(0);
    }
    
    //出力するやつ(サイズ注意)
    cv::Mat re_img = cv::Mat(500, 500, CV_8UC3);
    
    
    //変数の宣言
    int x, y, flag=0, i, j, k, l, m, c1=0, c2=0, maxc2=0, max, flag2=0; //制御用
    cv::Mat hsv_img, fin_img;
    cv::Vec3b s; //色値
    int Bc[370]; //青
    int Gc[370]; //緑
    int Rc[370]; //赤
    int tmp0, tmp1, tmp2;
    int be_size = 7;//ビーズサイズ (5 ~ 10)
    int range = (be_size * 2 - 1) / 2; //最頻値を求める範囲
    int tate = 10, yoko = 40;
    int hakoR[tate][yoko]; //色相
    int hakoG[tate][yoko]; //彩度
    int hakoB[tate][yoko]; //明度
    
    
    
//    faceClassifier.load("haarcascades/haarcascade_frontalface_default.xml");
//    std::vector<cv::Rect> faces;
//    
//    
//    faceClassifier.detectMultiScale(source_img, faces, 1.1, 3, 0, cv::Size(10,10));
    
    
    
    
    
    
    
//    for (k=0; k<faces.size(); k++) {
//        // 検出情報から顔の位置情報を取得
//        cv::Rect face = faces[k];
//        // 大きさによるチェック。
//        if (face.width*face.height < 10*10) {
//            continue;                                    // 小さい矩形は採用しない
//        }else{
//            
//            //認識した顔を四角形で覆う（デバック用に残しておいて）
////            cv::rectangle(source_img,
////                          cv::Point(face.x, face.y),
////                          cv::Point(face.x + face.width, face.y + face.height),
////                          CV_RGB(255, 0, 0),
////                          3, CV_AA);
//            
//            //正面の顔が認識できた合図
//            flag2 = 1;
//        }
//    }
    
    
    
    
    
        //色変換（BGR → HSV)
        cv::cvtColor (source_img, hsv_img, cv::COLOR_BGR2HSV);



        //画像の走査
        for (y=0; y<hsv_img.rows; y++) {
            for (x=0; x<hsv_img.cols; x++) {
                
                //色値取得
                s = hsv_img.at<cv::Vec3b>(y, x);
                
                //色判定（必ずHの値は全て網羅すること！）
                //くろ
                if (s[2] < 100) {
                    s[0] = 0;    //H: 色相
                    s[1] = 0;    //S: 彩度
                    s[2] = 0;    //V: 明度
                    hsv_img.at<cv::Vec3b>(y, x) = s;
                }
                //あか
                else if (s[0] < 12 && s[1] > 100) {
                    s[0] = 0;    //H: 色相
                    s[1] = 255;    //S: 彩度
                    s[2] = 255;    //V: 明度
                    hsv_img.at<cv::Vec3b>(y, x) = s;
                }
                //あか（Hが高い方）
                else if (s[0] > 175 && s[1] > 100) {
                    s[0] = 0;    //H: 色相
                    s[1] = 255;    //S: 彩度
                    s[2] = 255;    //V: 明度
                    hsv_img.at<cv::Vec3b>(y, x) = s;
                }
                //ピンク
                else if (s[0] > 129 && s[1] > 50) {
                    s[0] = 160;    //H: 色相
                    s[1] = 165;    //S: 彩度
                    s[2] = 255;    //V: 明度
                    hsv_img.at<cv::Vec3b>(y, x) = s;
                }else if (s[0] < 12 && s[1] > 10 && s[1] < 100 && s[2] > 150) { //薄い赤という認識
                    s[0] = 160;    //H: 色相
                    s[1] = 165;    //S: 彩度
                    s[2] = 255;    //V: 明度
                    hsv_img.at<cv::Vec3b>(y, x) = s;
                }
                //きいろ
                else if (s[0] > 24 && s[0] < 33 && s[1] > 50) {
                    s[0] = 30;    //H: 色相
                    s[1] = 255;    //S: 彩度
                    s[2] = 255;    //V: 明度
                    hsv_img.at<cv::Vec3b>(y, x) = s;
                }
                //オレンジ
                else if (s[0] > 11 && s[0] < 25 && s[1] > 50) {
                    s[0] = 18;    //H: 色相
                    s[1] = 255;    //S: 彩度
                    s[2] = 255;    //V: 明度
                    hsv_img.at<cv::Vec3b>(y, x) = s;
                }
                //きみどり
                else if (s[0] > 32 && s[0] < 87 && s[1] > 50) {
                    s[0] = 50;    //H: 色相
                    s[1] = 255;    //S: 彩度
                    s[2] = 255;    //V: 明度
                    hsv_img.at<cv::Vec3b>(y, x) = s;
                }
                //みずいろ
                else if (s[0] > 86 && s[0] < 130 && s[1] > 50) {
                    s[0] = 90;    //H: 色相
                    s[1] = 255;    //S: 彩度
                    s[2] = 255;    //V: 明度
                    hsv_img.at<cv::Vec3b>(y, x) = s;
                }
                //しろ
                else{
                    s[0] = 0;    //H: 色相
                    s[1] = 0;    //S: 彩度
                    s[2] = 255;    //V: 明度
                    hsv_img.at<cv::Vec3b>(y, x) = s;
                }
                
            }
        }


        //戻す
        cv::cvtColor (hsv_img, fin_img, cv::COLOR_HSV2BGR);



        //    //オープニング
        //    //収縮処理
        //    cv::erode(fin_img, fin_img, element, cv::Point(-1, -1), 5);
        //    //膨張処理
        //    cv::dilate(fin_img, fin_img, element, cv::Point(-1, -1), 5);
        //    
        //    //クロージング
        //    //膨張処理
        //    cv::dilate(fin_img, fin_img, element, cv::Point(-1, -1), 3);
        //    //収縮処理
        //    cv::erode(fin_img, fin_img, element, cv::Point(-1, -1), 3);






        //result_img
        cv::Mat result_img(cv::Size(fin_img.cols, fin_img.rows), CV_8UC3, cv::Scalar(255, 255, 255));


        for (y=be_size*2; y<fin_img.rows; y+=be_size*2) {
            
            //偶数奇数の判定
            flag++;
            
            //パターン１
            if (flag%2 == 1) {
                for (x=0; x<fin_img.cols; x+=be_size*2) {
                    
                    c1 = 0; //初期化
                    
                    //範囲内の色値取得
                    for (j=y-range; j<=y+range; j++) {
                        for (i=x-range; i<=x+range; i++) {
                            c1++;
                            s = fin_img.at<cv::Vec3b>(j, i);
                            Bc[c1] = s[0];
                            Gc[c1] = s[1];
                            Rc[c1] = s[2];
                        }
                    }
                    
                    //最頻値を調べる
                    for (i=1; i<=c1; i++) { //１つを決めて
                        tmp0 = Bc[i];
                        tmp1 = Gc[i];
                        tmp2 = Rc[i];
                        c2 = 0; //初期化
                        
                        for (j=1; j<=c1; j++) { //上で設定したやつと全てを比べる
                            if (tmp0 == Bc[j] && tmp1 == Gc[j] && tmp2 == Bc[j]) { //一致した場合
                                c2++;
                            }
                        }
                        
                        if (maxc2 < c2) { //それまでのより出現回数が多ければmax_cとmaxを更新する
                            maxc2 = c2;
                            max = i;
                        }
                            
                    }
                    
                    
                    //塗りつぶす方
                    cv::circle(result_img, cv::Point(x, y), be_size, cv::Scalar(Bc[max], Gc[max], Rc[max]), -1, CV_AA);
                    //輪郭の方
                    cv::circle(result_img, cv::Point(x, y), be_size, cv::Scalar(0, 0, 0), 1, CV_AA);
                }
            }else{  //パターン２
                for (x=be_size; x<fin_img.cols; x+=be_size*2) { //始まりが半歩遅れる
                    
                    c1 = 0; //初期化
                    
                    //範囲内の色値取得
                    for (j=y-range; j<=y+range; j++) {
                        for (i=x-range; i<=x+range; i++) {
                            c1++;
                            s = fin_img.at<cv::Vec3b>(j, i);
                            Bc[c1] = s[0];
                            Gc[c1] = s[1];
                            Rc[c1] = s[2];
                        }
                    }
                    
                    //最頻値を調べる
                    for (i=1; i<=c1; i++) { //１つを決めて
                        tmp0 = Bc[i];
                        tmp1 = Gc[i];
                        tmp2 = Rc[i];
                        c2 = 0; //初期化
                        
                        for (j=1; j<=c1; j++) { //上で設定したやつと全てを比べる
                            if (tmp0 == Bc[j] && tmp1 == Gc[j] && tmp2 == Bc[j]) { //一致した場合
                                c2++;
                            }
                        }
                        
                        if (maxc2 < c2) { //それまでのより出現回数が多ければmax_cとmaxを更新する
                            maxc2 = c2;
                            max = i;
                        }
                        
                    }
                    
                    
                    //塗りつぶす方
                    cv::circle(result_img, cv::Point(x, y), be_size, cv::Scalar(Bc[max], Gc[max], Rc[max]), -1, CV_AA);
                    //輪郭の方
                    cv::circle(result_img, cv::Point(x, y), be_size, cv::Scalar(0, 0, 0), 1, CV_AA);
                }
            }
            
        }





        //表示
        
        
        
        cv::imshow(WINDOW_NAME_OUTPUT, fin_img);
        cv::imshow("Source", source_img);
        cv::imshow(WINDOW_NAME_OUTPUT2, result_img);
    
    
    
    cv::waitKey();
    
    
    return 0;
}

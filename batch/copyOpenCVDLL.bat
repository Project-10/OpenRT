@echo off
SET version=430
SET OpenCV_src=%OPENCVDIR%\build\x64\vc16\bin

@echo on
copy %OpenCV_src%\opencv_core%version%.dll .\
copy %OpenCV_src%\opencv_highgui%version%.dll .\
copy %OpenCV_src%\opencv_imgproc%version%.dll .\
copy %OpenCV_src%\opencv_imgcodecs%version%.dll .\
copy %OpenCV_src%\opencv_videoio%version%.dll .\
                
copy %OpenCV_src%\opencv_core%version%d.dll .\
copy %OpenCV_src%\opencv_highgui%version%d.dll .\
copy %OpenCV_src%\opencv_imgproc%version%d.dll .\
copy %OpenCV_src%\opencv_imgcodecs%version%d.dll .\
copy %OpenCV_src%\opencv_videoio%version%d.dll .\


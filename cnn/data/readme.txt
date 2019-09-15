1. 原始数据集是28*28的bmp图片，分为 train 和 test 两个数据集, 然后 resize->32*32。
2. small系列数据集是原始test数据集拆分出来的三个数据集，因为比较小，所以方便测试。
3. train数据集拆分成train_image与valid_image数变成据集，test数据集->test_image数据集。
4. 原始的train 数据集被标记为train_imagx,train_imagx=train_image+valid_image。
5. todo需要在代码中解决train_image和valid_image的分开的问题，而不是靠建文件夹分开。

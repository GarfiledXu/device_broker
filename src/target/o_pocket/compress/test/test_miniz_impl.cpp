#include "miniz_impl.inl"


inline int test_miniz(int argc, char** argv){
    #if 0
    int ret = 0;
    std::string input1 = argv[1];
    std::string input2 = argv[2];
    std::string input3 = argv[3];
    std::string input4 = argv[4];
    for (int i = 0;i<1;i++) {
        SLOGI("i = {}", i);

    // fs::remove_all(input3);

    auto start_time = std::chrono::steady_clock::now();
    mz_zip_archive miniz_handle_;
    std::string output_zip_file = "test_zip.zip";
    // printf("start init miniz archive\n");
    // ret = init_miniz_archive(miniz_handle_, output_zip_file);
    // if (ret) {
    //     printf("init miniz archive error! ret:%d\n", ret);
    //     exit(1);
    // }
    if (input1 == "1") {
        //diretory
        //1. 同一个目录下的几个子文件夹，依次添加 pass
        //2./a/b /a/b/c /a/b/c/d 间隔几个子文件夹，拥有共同目录 pass
        //3./a/b /a/b/c /b/c/a 有非relateive的  pass
        //file
        //1. 同一个目录下多个文件 pass
        //2. 文件和文件夹混合 pass

        printf("enter input1\n");
        MinizCompressFile compresser(output_zip_file);
        auto func_append = [&](const std::string& input_file) {
            // ret = append_to_miniz_direct(miniz_handle_, input_file, false);
            
            ret = compresser.append_direct(input_file, false);

            if (ret) {
                printf("append fail! %s, ret:%d\n", input_file.c_str(), ret);
                exit(1);
            }
        };
        func_append(argv[2]);
        func_append(argv[3]);
        func_append(argv[4]);
    }
    else if (input1 == "2") {
        printf("enter input1\n");
        //diretory
        //1. 1/2/3 /a/b /a/b/c  pass
        //2. 1/2/3  /a/b /c/d /f/d pass
        //3. /a/b /a/b/c /a/b/d pass
        //file
        //1. 1/2 /3  /a/b/c.txt /a/c/b.txt pass
        //2. 文件和文件夹混合 pass
        MinizCompressFile compresser(output_zip_file);
        auto func_append = [&](const std::string& input_file) {
            // ret = append_to_miniz_relative(miniz_handle_, input_file, argv[2],  true);
            SLOGD("input_file:{}, relative:{}", input_file, argv[2]);
            ret = compresser.append_relative(input_file, argv[2], true);
            if (ret) {
                printf("append fail! %s, ret:%d\n", input_file.c_str(), ret);
                exit(1);
            }
        };
        func_append(argv[3]);
        func_append(argv[4]);
        func_append(argv[5]);
        
    }
    else if (input1 == "3") {
        //1. normal compress, contain src fodler pass
        //2. not contain src folder pass
        //3.stress test pass
        ret = MinizCompressFile::recursive_decompress(input2, input3, std::stoi(input4));
         if (ret) {
            printf("recursive_decompress fail! %d\n", ret);
            exit(1);
        }
    }
    // ret = uninit_miniz_archive(miniz_handle_);
    // if (ret) {
    //     printf("uninit miniz archive error! ret:%d\n", ret);
    //     exit(1);
    // }
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time taken: " << duration.count() << " milliseconds ret:" << ret<< std::endl;

    }
    #endif
}
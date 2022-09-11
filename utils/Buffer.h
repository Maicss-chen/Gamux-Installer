//
// Created by maicss on 22-9-11.
//

#ifndef BUFFER_BUFFER_H
#define BUFFER_BUFFER_H

#include <cstdio>
#include <semaphore.h>
#include <mutex>

#define BUFFER_SIZE 8388608 // 8MB

class Buffer {
public:
    /**
     * 该标志的作用是用于判断当前流的状态。假设在缓冲区使用过程中，输出流每次从缓冲区中取出8k的数据，输入流已经将所有数据输入完毕，且输出总数据长
     * 度不是8k的倍数时，则最终输出流部分将因无法得到完整的8k数据而阻塞，这是危险的。因此引入Flag机制。
     */
    typedef enum {

        /// 当正常状态下（输入流尚未结束）则Flag应当置为此。此时输入输出正常进行。
        BUFFER_FLAG_NORMAL,

        /// 当输入流已经结束，应当将Flag置为此。因此当取数据时，需要首先判断此项，若检测到输入流已结束时，可使用popAll()方法将缓冲区的剩余数据
        /// 全部拿出，当然这个调用的时机由开发者自行决定，并非必要。
        BUFFER_FLAG_END
    } flag;

    /**
     * 创建一个Buffer对象，并为其申请内存空间，默认为8MB,可指定需要的大小。
     * @param size 指定Buffer的尺寸，默认为8M，单位是字节。
     */
    explicit Buffer(size_t size = BUFFER_SIZE);

    /**
     * 向缓冲区传入指定长度的数据，若缓冲区没有空闲空间则等待。
     * @param data 指向传入数据的指针。
     * @param length 数据的长度。
     */
    void push(char *data, size_t length);

    /**
     * 从缓冲区读取指定长度的数据，若缓冲区中没有所需长度的数据则等待。
     * @param data 要接受数据的指针，需要提前申请内存空间。
     * @param length 要获取数据的长度。
     */
    void pop(char *data, size_t length);

    /**
     * 获取缓冲区剩余空间。
     * @return 返回缓冲区剩余空间。
     */
    [[nodiscard]] size_t getFreeSize() const;

    /**
     * 获取缓冲区大小。
     * @return 返回缓冲区大小。
     */
    [[nodiscard]] size_t getBufferSize() const;

    /**
     * 取出缓冲区中现存的所有数据。
     * @param data 指针指向存储取出的所有数据的内存区域。
     * @param length 返回取出的数据的长度。
     */
    void popAll(char *data, size_t &length);

    /**
     * 获得一个标志，该标志用于判定该缓冲区的状态。
     * @return 返回标志
     */
    flag getFlag();

    /**
     * 设置标志，该标志用于判断缓冲区状态。
     * @param f 要设置的标志
     */
    void setFlag(flag f);

private:
    char *m_buf;
    char *m_read;
    char *m_write;
    size_t m_free_size;
    sem_t m_sem_pop;
    sem_t m_sem_push;
    std::mutex m_lock;
    const size_t m_buffer_size;
    flag m_flag;
};


#endif //BUFFER_BUFFER_H

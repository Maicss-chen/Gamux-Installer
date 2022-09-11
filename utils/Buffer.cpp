//
// Created by maicss on 22-9-11.
//

#include <cstring>
#include "Buffer.h"


Buffer::Buffer(size_t size)
    : m_buf(new char[size])
    , m_write(m_buf)
    , m_read(m_buf)
    , m_free_size(size)
    , m_buffer_size(size)
    , m_flag(BUFFER_FLAG_NORMAL)
{
    sem_init(&m_sem_pop, 0, 0);
    sem_init(&m_sem_push, 0, 0);
}

void Buffer::push(char *data, size_t length) {

    if (m_flag == BUFFER_FLAG_END) {
        printf("警告：在Flag置为BUFFER_FLAG_END后，仍然往缓冲区里输入了数据。");
    }

    while (getFreeSize() < length) {
        sem_wait(&m_sem_push);
    }

    m_lock.lock();

    size_t far_to_end = getBufferSize() - (m_write - m_buf);

    if (far_to_end < length) {
        memcpy(m_write, data, far_to_end);
        m_write = m_buf;
        data += far_to_end;
        memcpy(m_write, data, length - far_to_end);
    }

    memcpy(m_write, data, length);
    m_write += length;
    m_free_size -= length;
    sem_post(&m_sem_pop);
    m_lock.unlock();
}

void Buffer::pop(char *data, size_t length) {

    while (getBufferSize() - getFreeSize() < length){
        sem_wait(&m_sem_pop);
    }

    m_lock.lock();

    size_t far_to_end = getBufferSize() - (m_read - m_buf);

    if (far_to_end < length) {
        memcpy(data, m_read, far_to_end);
        m_read = m_buf;
        data += far_to_end;
        memcpy(data, m_read, length - far_to_end);
    }

    memcpy(data, m_read, length);
    m_read += length;
    m_free_size += length;
    sem_post(&m_sem_push);
    m_lock.unlock();
}

size_t Buffer::getFreeSize() const {
    return m_free_size;
}

size_t Buffer::getBufferSize() const {
    return m_buffer_size;
}

void Buffer::popAll(char *data, size_t &length) {
    length = getBufferSize() - getBufferSize();
    pop(data, length);
}

Buffer::flag Buffer::getFlag() {
    return m_flag;
}

void Buffer::setFlag(Buffer::flag f) {
    m_flag = f;
}

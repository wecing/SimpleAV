#ifndef __SA__API__H__DEFINED__
#define __SA__API__H__DEFINED__

#include "SAQueue.h"

#include <SDL/SDL.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>

#define  SAABUFFER_SIZE ((AVCODEC_MAX_AUDIO_FRAME_SIZE) * 3 / 2)

typedef struct SAVideoPacket {
     AVFrame *frame_ptr;
     double pts;
} SAVideoPacket;

typedef struct SAAudioPacket {
     uint8_t *abuffer;
     int len;
     double pts;
} SAAudioPacket;

typedef struct SAContext {
     char *filename;
     SAQContext *vq_ctx, *aq_ctx;
     SDL_mutex *decode_lock; // FIXME: remove SA's dependency of SDL.
     AVFormatContext *avfmt_ctx_ptr;
     AVCodecContext *a_codec_ctx, *v_codec_ctx;
     AVStream *audio_st, *video_st;
     AVCodec *a_codec, *v_codec;
     int v_stream, a_stream;
     int v_width, v_height;
     AVFrame *v_frame_t;
     int audio_eof, video_eof;
     double video_clock;
} SAContext;

int SA_init(void);

SAContext *SA_open(char *);

void SA_close(SAContext *);

SAAudioPacket *SA_get_ap(SAContext *);

SAVideoPacket *SA_get_vp(SAContext *);

void SA_seek(SAContext *, double, double);

int _SA_decode_packet(SAContext *);

int _SA_get_buffer(AVCodecContext *, AVFrame *);

void _SA_release_buffer(AVCodecContext *, AVFrame *);

#endif

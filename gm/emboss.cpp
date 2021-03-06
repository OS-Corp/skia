/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "gm.h"
#include "SkBlurMaskFilter.h"
#include "SkCanvas.h"
#include "SkColorFilter.h"

#include "SkColorFilter.h"
static SkBitmap make_bm() {
    SkBitmap bm;
    bm.allocN32Pixels(100, 100);

    SkCanvas canvas(bm);
    canvas.clear(0);
    SkPaint paint;
    paint.setAntiAlias(true);
    canvas.drawCircle(50, 50, 50, paint);
    return bm;
}

class EmbossGM : public skiagm::GM {
public:
    EmbossGM() {
    }

protected:
    virtual SkString onShortName() SK_OVERRIDE {
        return SkString("emboss");
    }

    virtual SkISize onISize() SK_OVERRIDE {
        return SkISize::Make(600, 120);
    }

    virtual void onDraw(SkCanvas* canvas) SK_OVERRIDE {
        SkPaint paint;
        SkBitmap bm = make_bm();
        canvas->drawBitmap(bm, 10, 10, &paint);

        const SkScalar dir[] = { 1, 1, 1 };
        paint.setMaskFilter(SkBlurMaskFilter::CreateEmboss(3, dir, 0.3f, 0.1f))->unref();
        canvas->translate(bm.width() + SkIntToScalar(10), 0);
        canvas->drawBitmap(bm, 10, 10, &paint);

        // this combination of emboss+colorfilter used to crash -- so we exercise it to
        // confirm that we have a fix.
        paint.setColorFilter(SkColorFilter::CreateModeFilter(0xFFFF0000, SkXfermode::kSrcATop_Mode))->unref();
        canvas->translate(bm.width() + SkIntToScalar(10), 0);
        canvas->drawBitmap(bm, 10, 10, &paint);
    }

private:
    typedef skiagm::GM INHERITED;
};

DEF_GM( return SkNEW(EmbossGM); )

/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.tangide.canvas;

// Wrapper for native library

public class CanvasJNI {

     static {
         System.loadLibrary("cantkrt");
     }

    /**
     * @param width the current view width
     * @param height the current view height
     */
     public static native void surfaceCreated();
     public static native void surfaceChanged(int width, int height);
     public static native void render();
     public static native void dispatchKeyDown(int code);
     public static native void dispatchKeyUp(int code);
     public static native void dispatchTouchEvent(int action, int n, int[] x, int[] y);
}

struct FFT{
	static void _fft(vector<cpx> & a, bool invert) {
	    int n = a.size();

			for (int i = 1, j = 0; i < n; i++) {
		        int bit = n >> 1;
		        for (; j & bit; bit >>= 1)
		            j ^= bit;
		        j ^= bit;
		
		        if (i < j)
		            swap(a[i], a[j]);
		    }
	
	    for (int len = 2; len <= n; len <<= 1) {
	        db ang = 2 * pi / len * (invert ? -1 : 1);
	        cpx wlen(cos(ang), sin(ang));
	        int end = len >> 1;
	        for (int i = 0; i < n; i += len) {
	        	cpx w(1);
	            for (int j = 0; j < end; j++) {
	                cpx u = a[i+j], v = a[i+j+end] * w;
	                a[i+j] 		= u + v;
	                a[i+j+end] 	= u - v;
	                w *= wlen;
	            }
	        }
	    }
	
	    if (invert) {
	        for (cpx & x : a)
	            x /= n;
	    }
	}
	
    static vi multiply(vi const& a, vi const& b) {
	    vt<cpx> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	    int n = 1;
	    while (n < a.size() + b.size()) 
	        n <<= 1;
		fa.resize(n); fb.resize(n);
	
	    _fft(fa, false);
	    _fft(fb, false);
	    
	    for (int i = 0; i < n; i++)
	        fa[i] *= fb[i];

	    _fft(fa, true);
	
		int len = a.size() + b.size() - 1;
	    vi result(len);
	    for (int i = 0; i < len; i++)
	    {
	    	result[i] = round(fa[i].real());
		}	        
	    return result;
	}
};

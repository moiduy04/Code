// might NOT actually work properly
struct NTT{
	const static li root_pw = 1 << 20;
	
// Manually add constraints before using NTT
// by adding mod, then run the init() function.
	const static li mod = 998244353;
	
	static li mod_inverse(int n, int k) 
	{
		int x = 1;
		for (; k; k >>= 1) 
		{
			if (k&1) 
				x = x * n % mod;
			n = n * n % mod;
		} 
		return x;
	}
		
	static void init(){
		li _ 	= 2;
		while(!(mod_inverse(_, root_pw) == 1 && mod_inverse(_, root_pw >> 1) != 1)){
			++_;
		}
		li _1 = mod_inverse(_, mod-2);
		cout << "root is " 		<< _	<< endl;
		cout << "root_1 is "	<< _1	<< endl;
	}
//	Put constraints here:
	const static li root 	= 31;		
	const static li root_1 	= 128805723;
	
	static void _ntt(vli & v, bool invert){
	    int n = v.size();
	    for (int i = 1, j = 0; i < n; i++) 
		{
	        int bit = n>>1;
	        for (; j & bit; bit >>= 1)
	            j ^= bit;
	        j ^= bit;
	        if (i < j)
	            swap(v[i], v[j]);
	    }
	 	for (int len = 2; len <= n; len <<= 1)
		{
	        li wn = invert ? root_1 : root;
	        for (int i = len; i < root_pw; i <<= 1)
	            wn = (li)(1LL * wn * wn % mod);
			int end = len >> 1;
	        for (int i = 0; i < n; i += len)
			{
	            li w = 1;
	            for (int j = 0; j < end; j++) 
				{
	                li b = v[i+j], c = (li)(1LL * v[i+j+end] * w % mod);
	                v[i+j] 		= b + c < mod ? b + c : b + c - mod;
	                v[i+j+end] 	= b - c > -1  ? b - c : b - c + mod;
	                w = (li)(1LL * w * wn % mod);
	            }
	        }
	    }
	 
	    if (invert)
		{
	        li n_1 = mod_inverse(n, mod-2);
	        for (li & x : v)
	            x = (li)(1LL * x * n_1 % mod);
	    }
	}
};

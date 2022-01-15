namespace celer {
	class Version
	{
	public:
		Version(){}
		Version(unsigned int maj, unsigned int min, unsigned int mic) {
			major = maj;
			minor = min;
			micro = mic;
		}
		unsigned int major;
		unsigned int minor;
		unsigned int micro;
	};
}
#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <sstream>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};
class Max : public IStatistics {
public:
	Max() : m_max{std::numeric_limits<double>::max()*-1} {};
	void update(double next) override{
		if (m_max<next){
			m_max = next;
		}
	};
	double eval() const override {
		return m_max;
	}
	const char* name() const override {
		return "max";
	}
private:
	double m_max;
};
class MeanList : public IStatistics {
public:
	MeanList() {};
	void update(double next) override {
		values.push_back(next);
	}
	double eval() const override {
		double j = 0;
		for (int i = 0; i<values.size(); i++)
		{
			j+=values[i];
		}
		return j/values.size();
	}
	const char* name() const override{
		return "mean list";
	}

private:
	std::vector<double>values;	
};
class MeanSum : public IStatistics {
public:
	MeanSum() : sum(0), count(0) {};

	void update(double next) override {sum+=next; count++;};	
	double eval() const override {return sum/count;};
	const char* name() const override {return "mean sum";};

private:
	double sum;
	int count;
};
class MeanResult : public IStatistics {
public:
	MeanResult() : result(0), count(0) {};
	void update(double next) override
	{
		result *= count; 
		result += next;
		++count;
		result /= count;
	};
	double eval() const override {
		return result;
	}

	const char* name() const override {
		return "mean result";
	}
private:
	double result;
	int count;
};
class StdList : public IStatistics {
public:
	StdList() : m_mean_sum(0) {};
	void update(double next) override {values.push_back(next); m_mean_sum+=next;};
	
	double eval() const override {
		double sum = 0;
		int size = values.size();
		double mean_result = m_mean_sum / size;
		double prom;
		for (int i = 0; i<size; i++)
		{
			prom = values[i] - mean_result;
			prom *= prom;
			sum += prom;
		}
		sum /= size;
		return std::sqrt(sum);
	};
	const char* name() const override {return "std list";};
private:
	int m_mean_sum;
	std::vector<double>values;
	double evalConsult() const {
		double sum = 0;
		int size = values.size();
		std::cout << "sum mean: " << m_mean_sum << std::endl;
		double mean_result = m_mean_sum / size;
		std::cout << "result mean: " << mean_result << std::endl;
		double prom;
		std::cout << std::endl;
		for (int i = 0; i<size; i++)
		{
			prom = values[i] - mean_result;
			std::cout << "prom: " << prom << std::endl;
			prom *= prom;
			std::cout << "prom^2: " << prom << std::endl;
			sum += prom;
		}
		std::cout << std::endl;
		std::cout << "std sum: " << sum << std::endl;
		sum /= size;
		std::cout << "mean std: " << sum << std::endl;
		std::cout << "result: " << std::sqrt(sum) << std::endl;

		return std::sqrt(sum);
	};
};

template<size_t statistics_count>
bool Logic(IStatistics *statistics[])
{


	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}


	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return true;
}
int main(int argc, char**argv) {

	std::ifstream ifstr(argv[1]);
	std::streambuf* CIN_buf;
	if (argc>1)
		CIN_buf = std::cin.rdbuf(ifstr.rdbuf());
	else
		CIN_buf = std::cin.rdbuf();

	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new MeanSum{};	
	statistics[3] = new MeanList{};
	statistics[4] = new MeanResult{};
	statistics[5] = new StdList{};

	Logic<statistics_count>(statistics);

	std::cin.rdbuf(CIN_buf);

	return 0;
}
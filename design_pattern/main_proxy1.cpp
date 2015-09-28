#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "fwd.h"

namespace design_pattern {
    class Description {
    };

    class IDescriptionReader {
    public:
        virtual ~IDescriptionReader() {}
        virtual const std::size_t numberOfDescription() const = 0;
        virtual const date_t& today() const = 0;
        virtual const Description& operator()(const std::size_t index) = 0;
    };

    class DescriptionReader : public IDescriptionReader {
    public:
        DescriptionReader(const std::string& filePath)
        : _today(), _descriptions()
        {
            // TODO
            // read all descriptions of the file.
        }

        virtual ~DescriptionReader() {}

        virtual const std::size_t numberOfDescription() const
        {
            return _descriptions.size();
        }

        virtual const date_t& today() const
        {
            return _today;
        }

        virtual const Description& operator()(const std::size_t index)
        {
            return _descriptions[index];
        }

    private:
        const date_t _today;
        const std::vector<Description> _descriptions;
    };

    class ProxyReader : public IDescriptionReader {
    public:
        ProxyReader(const std::string& filePath)
        : _today(), _numberOfDescription(), _filePath(filePath), _readerPtr()
        {
            // TODO
            // just read today and numberOfDescription from the file.
        }

        virtual ~ProxyReader() {}

        virtual const std::size_t numberOfDescription() const
        {
            return _numberOfDescription;
        }

        virtual const date_t& today() const
        {
            return _today;
        }

        virtual const Description& operator()(const std::size_t index)
        {
            if (_readerPtr == NULL) {
                _readerPtr = boost::make_shared<DescriptionReader>(_filePath);
            }
            return (*_readerPtr)(index);
        }

    private:
        date_t _today;
        const std::string _filePath;
        std::size_t _numberOfDescription;
        boost::shared_ptr<DescriptionReader> _readerPtr;
    };

}


int main()
{
    const std::string filePath = "hoge.txt";

    {
        // read all file data.
        design_pattern::DescriptionReader reader(filePath);
        std::cout << reader.today() << std::endl;
    }

    {
        // just read today and numberOfDescription
        design_pattern::ProxyReader reader(filePath);
        std::cout << reader.today() << std::endl;
        // lazy read for Descriptions
        //std::cout << reader(5) << std::endl;
    }
    return 0;
}
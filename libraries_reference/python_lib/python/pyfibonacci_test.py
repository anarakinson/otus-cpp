import fibonacci
import pytest


def test_calc_small():
    assert 55 == fibonacci.calc(10)
    assert 6765 == fibonacci.calc(20)


def test_calc_small_external():
    assert 55 == fibonacci.calc_externally(10)
    assert 6765 == fibonacci.calc_externally(20)


def test_calc_big():
   assert 1548008755920 == fibonacci.calc(60)


def test_calc_big_externally():
    assert 1548008755920 == fibonacci.calc_externally(60)


def test_series():
    expected = [0, 5, 55]

    calc = fibonacci.SeriesCalculator()

    calc.put_index(0)
    calc.put_index(5)
    calc.put_index(10)

    assert expected == calc.calc()


def test_series_externally():
    expected = [0, 5, 55]

    calc = fibonacci.ExternalSeriesCalculator()

    calc.put_index(0)
    calc.put_index(5)
    calc.put_index(10)

    assert expected == list(calc.calc())

        
        
@pytest.mark.skip(reason="no way of currently testing this")
def testing(foo, name, *args, **kwargs):
    start_time = time.time()
    print(f"Testing: {name}")
    foo()
    end_time = time.time()
    print("PASSED")
    print(f"{end_time - start_time : .10f}")
    print()


if __name__ == "__main__":
    import time

    testing(test_calc_small, "test_calc_small")
    testing(test_calc_small_external, "test_calc_small_external")
    testing(test_calc_big, "test_calc_big")
    testing(test_calc_big_externally, "test_calc_big_externally")
    testing(test_series, "test_series")
    testing(test_series_externally, "test_series_externally")

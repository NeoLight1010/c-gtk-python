import time


def hello(name: str) -> str:
    max_time = 3
    start_time = time.time()

    while (time.time() - start_time) < max_time:
        pass

    return f"Hello {name}!"

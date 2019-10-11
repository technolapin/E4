test = {
  'name': 'slicing',
  'points': 8,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> print(A)
          [1 2 3]
          """,
          'hidden': False,
          'locked': False
        },
        {
          'code': r"""
          >>> print(B)
          [ 1  4  7 10]
          """,
          'hidden': False,
          'locked': False
        },
        {
          'code': r"""
          >>> print(C)
          [[ 8  9]
           [11 12]]
          """,
          'hidden': False,
          'locked': False
        },
        {
          'code': r"""
          >>> print(D)
          [[1 2 3]
           [7 8 9]]
          """,
          'hidden': False,
          'locked': False
        },
        {
          'code': r"""
          >>> print(E)
          [[1 2]
           [4 5]]
          """,
          'hidden': False,
          'locked': False
        },
        {
          'code': r"""
          >>> print(F)
          [[ 1  3]
           [ 4  6]
           [ 7  9]
           [10 12]]
          """,
          'hidden': False,
          'locked': False
        },
        {
          'code': r"""
          >>> print(G)
          [[ 4  5  6]
           [10 11 12]]
          """,
          'hidden': False,
          'locked': False
        },
        {
          'code': r"""
          >>> print(H)
          [[2 3]
           [5 6]]
          """,
          'hidden': False,
          'locked': False
        }
      ],
      'scored': True,
      'setup': '',
      'teardown': '',
      'type': 'doctest'
    }
  ]
}

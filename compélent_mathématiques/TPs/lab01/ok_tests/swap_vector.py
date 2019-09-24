test = {
  'name': 'swap_vector',
  'points': 2,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> print(vector)
          [4 2 8 7 1 3]
          """,
          'hidden': False,
          'locked': False
        },
        {
          'code': r"""
          >>> print(swapped)
          75e9204a57b119e0dc8d0130f13c0266
          # locked
          """,
          'hidden': False,
          'locked': True
        }
      ],
      'scored': True,
      'setup': '',
      'teardown': '',
      'type': 'doctest'
    }
  ]
}
